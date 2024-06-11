/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_final.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:47:07 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 10:24:26 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	handle_execute(t_minishell *shell, t_redirect *redirect_array,
	int index)
{
	if (redirect_array[index].argv != NULL
		&& check_builtins(redirect_array[index].argv[0]) == 1)
	{
		execute_builtins(ft_strlen_map(redirect_array[index].argv),
			redirect_array[index].argv, shell);
		free_minishell(shell);
		exit(EXIT_SUCCESS);
	}
	else if (redirect_array[index].argv != NULL
		|| redirect_array[index].argv[0][0] == '$')
	{
		if (access(redirect_array[index].argv[0], F_OK) == 0)
			execve(redirect_array[index].argv[0], redirect_array[index].argv,
				shell->env);
		if (is_file(redirect_array[index].argv[0]) == 0)
		{
			ft_putstr_fd("minishell: Is a directory:"
				" You need to use a command\n", 2);
			exit(126);
		}
		free_minishell(shell);
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
}

void	ft_exec(t_redirect *redirect_array, int index, t_minishell *shell,
		int pipes[MAX_PIPES][2])
{
	pid_t	pid;

	if (index < shell->nb_cmds - 1)
		pipe(pipes[index]);
	signal(SIGINT, handle_nothing);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		handle_dup_close(index, redirect_array, shell, pipes);
		handle_execute(shell, redirect_array, index);
	}
	else if (index < shell->nb_cmds - 1)
	{
		if (pipes[index][WRITE_END] != -1)
			close(pipes[index][WRITE_END]);
	}
	signal(SIGINT, handle_sigint);
}
