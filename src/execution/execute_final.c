/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_final.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:47:07 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/18 12:00:45 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd_pipe(int pipes[MAX_PIPES][2])
{
	int	i;

	i = 0;
	while (i < MAX_PIPES)
	{
		if (pipes[i][WRITE_END] != -1)
			close(pipes[i][WRITE_END]);
		if (pipes[i][READ_END] != -1)
			close(pipes[i][READ_END]);
		i++;
	}
}

static void	handle_infile_outfile(t_redirect *redirect_array, int index)
{
	if (redirect_array[index].outfile.fd != -1)
	{
		dup2(redirect_array[index].outfile.fd, STDOUT_FILENO);
		if (redirect_array[index].outfile.fd != -1)
			close(redirect_array[index].outfile.fd);
	}
	if (redirect_array[index].infile.fd != -1)
	{
		dup2(redirect_array[index].infile.fd, STDIN_FILENO);
		if (redirect_array[index].infile.fd != -1)
			close(redirect_array[index].infile.fd);
	}
}

static void	handle_dup_close(int index, t_redirect *redirect_array,
		t_minishell *shell, int pipes[MAX_PIPES][2])
{
	if (shell->redirect_array[index].infile.fd == -2
		|| shell->redirect_array[index].outfile.fd == -2)
	{
		free_minishell(shell);
		close_fd_pipe(pipes);
		exit(1);
	}
	if (index < shell->nb_cmds - 1)
	{
		dup2(pipes[index][WRITE_END], STDOUT_FILENO);
		if (pipes[index][WRITE_END] != -1)
			close(pipes[index][WRITE_END]);
		if (pipes[index][READ_END] != -1)
			close(pipes[index][READ_END]);
	}
	if (index > 0)
	{
		dup2(pipes[index - 1][READ_END], STDIN_FILENO);
		if (pipes[index - 1][WRITE_END] != -1)
			close(pipes[index - 1][WRITE_END]);
		if (pipes[index - 1][READ_END] != -1)
			close(pipes[index - 1][READ_END]);
	}
	handle_infile_outfile(redirect_array, index);
}

void	ft_exec(t_redirect *redirect_array, int index, t_minishell *shell,
		int pipes[MAX_PIPES][2])
{
	pid_t	pid;

	if (index < shell->nb_cmds - 1)
		pipe(pipes[index]);
	signal(SIGINT, handle_nothing);
	pid = fork();
	redirect_array->pid = pid;
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		handle_dup_close(index, redirect_array, shell, pipes);
		handle_execute(shell, redirect_array, index);
	}
	else if (index < shell->nb_cmds - 1)
		if (pipes[index][WRITE_END] != -1)
			close(pipes[index][WRITE_END]);
	g_exit_signal = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit_two);
}
