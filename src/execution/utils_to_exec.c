/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:50:40 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 13:25:27 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	counter_dollars(const char *content)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	if (content != NULL)
	{
		while (content[i] != '\0')
		{
			if (content[i] == '$')
				counter++;
			i++;
		}
	}
	return (counter);
}

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d: %s\n", i++, (char *)list->content);
		list = list->next;
	}
}

int	len_to_dollars(const char *content, int index)
{
	int		len;

	len = 0;
	if (content[index] != '$')
		return (0);
	while (content[index] != ' ' && content[index] != '\0')
	{
		index++;
		len ++;
	}
	return (len);
}

char	*get_variable_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_strdup(env[i] + 4);
			if (path == NULL)
			{
				perror("Error malloc path");
				exit(EXIT_FAILURE);
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	check_file_in_directory(DIR *dir, char *path, char *file)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, file) == 0)
		{
			closedir(dir);
			free(path);
			return (1);
		}
		entry = readdir(dir);
	}
	return (0);
}
