/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:10:16 by lauger            #+#    #+#             */
/*   Updated: 2024/06/11 10:23:50 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_command_in_directory(const char *cmd, const char *directory)
{
	size_t	command_path_len;
	char	*command_path;

	command_path_len = ft_strlen(directory) + ft_strlen(cmd) + 2;
	command_path = ft_calloc(sizeof(char), command_path_len);
	if (!command_path)
		return (NULL);
	ft_strcat(command_path, directory);
	ft_strcat(command_path, "/");
	ft_strcat(command_path, cmd);
	return (command_path);
}

static char	*locate_executable_command(const char *cmd, char **directories)
{
	char	*command_path;
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (directories[i] != NULL)
	{
		command_path = find_command_in_directory(cmd, directories[i]);
		if (!command_path)
			i++;
		else if (access(command_path, F_OK) == 0)
		{
			result = command_path;
			break ;
		}
		else
		{
			free(command_path);
			i++;
		}
	}
	ft_free_tab(directories);
	return (result);
}

static void	*search_path(char *env[], int i, char *path)
{
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_substr(env[i], 5, ft_strlen(env[i]) - 4);
			if (!path)
				return (NULL);
			break ;
		}
	}
	return (path);
}

int	is_path(const char *cmd)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "/", 1) == 0)
		return (1);
	else
		return (0);
}

char	*check_command_existence(char *cmd, char *env[])
{
	char	*path;
	char	*result;
	char	**tab_directories;
	int		i;

	path = NULL;
	i = -1;
	if (is_path(cmd) == 1)
		return ((char *)cmd);
	path = search_path(env, i, path);
	if (path == NULL)
		return (NULL);
	tab_directories = ft_split(path, ':');
	free(path);
	if (!tab_directories)
		return (NULL);
	result = locate_executable_command(cmd, tab_directories);
	if (!result)
		return (cmd);
	free(cmd);
	return (result);
}
