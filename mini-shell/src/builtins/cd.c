/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:31:53 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/28 10:31:56 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path(t_token *tokens, char **env, int *exit_status)
{
	char	*path;

	if (tokens->next == NULL)
		path = ft_getenv("HOME", env);
	else
	{
		if (tokens->next->next != NULL)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			*exit_status = 1;
			return (NULL);
		}
		path = tokens->next->value;
	}
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*exit_status = 1;
	}
	return (path);
}

static void	handle_cd_error(char *path, int *exit_status)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	*exit_status = 1;
}

static void	change_directory(char *path, int *exit_status)
{
	int	ret;

	if (!path)
		return ;
	ret = chdir(path);
	if (ret == -1)
		handle_cd_error(path, exit_status);
	else
		*exit_status = 0;
}

void	ft_cd(t_token *tokens, char **env, int *exit_status)
{
	char	*path;

	path = get_path(tokens, env, exit_status);
	change_directory(path, exit_status);
}
