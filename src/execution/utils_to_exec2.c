/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:24:42 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 15:43:32 by lauger           ###   ########.fr       */
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

	if (!path)
		return (-1);
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
	int		status;
	int		last_status;
	int		nb_cmds;

	last_status = shell->exit_status;
	signal(SIGINT, handle_sigint_without_prefix);
	waitpid(shell->redirect_array[shell->nb_cmds - 1].pid, &status, 0);
	close_fd_pipe(shell->pipes);
	nb_cmds = shell->nb_cmds;
	while (0 < nb_cmds)
	{
		waitpid(shell->redirect_array[nb_cmds - 1].pid, &status, 0);
		nb_cmds--;
	}
	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		last_status = WEXITSTATUS(status);
	signal(SIGINT, handle_sigint);
	return (last_status);
}

int	is_not_token_word(t_token *current)
{
	if (current->next->type == TOKEN_PIPE
		|| current->next->type == TOKEN_REDIRECT_IN
		|| current->next->type == TOKEN_REDIRECT_OUT
		|| current->next->type == TOKEN_DOUBLE_REDIRECT_OUT
		|| current->next->type == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}
