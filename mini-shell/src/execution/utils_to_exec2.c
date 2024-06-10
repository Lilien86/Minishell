/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:24:42 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/10 17:49:34 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_exist_in_directory(char *path, char *file)
{
	DIR				*dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}
	if (check_file_in_directory(dir, path, file))
		return (1);
	if (access(file, F_OK) == 0 && access(file, X_OK) == -1)
	{
		closedir(dir);
		free(path);
		return (1);
	}
	closedir(dir);
	free(path);
	return (0);
}

int	is_file(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (-1);
	if (S_ISREG(statbuf.st_mode))
		return (1);
	else if (S_ISDIR(statbuf.st_mode))
		return (0);
	else
		return (-1);
}

void	init_pipes(int pipes[MAX_PIPES][2])
{
	int	i;

	i = 0;
	while (i < MAX_PIPES)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
}

int	handle_wait(t_minishell *shell)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	pid;

	i = 0;
	last_status = shell->exit_status;
	while (i < shell->nb_cmds)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			break ;
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = WTERMSIG(status);
		i++;
	}
	return (last_status);
}
