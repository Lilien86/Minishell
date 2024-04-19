/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:21:10 by lauger            #+#    #+#             */
/*   Updated: 2024/04/19 10:32:22 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child(t_redirect *redirect, t_minishell *shell)
{
	if (redirect->infile.fd != STDIN_FILENO)
	{
		if (dup2(redirect->infile.fd, STDIN_FILENO) == -1)
			error_exit("dup2", shell);
		close(redirect->infile.fd);
	}
	if (redirect->outfile.fd != STDOUT_FILENO)
	{
		if (dup2(redirect->outfile.fd, STDOUT_FILENO) == -1)
			error_exit("dup2", shell);
		close(redirect->outfile.fd);
	}
	if (access(redirect->argv[0], X_OK) == -1)
	{
		ft_printf("Error: %s is not executable or does not exist.\n",
			redirect->argv[0]);
		exit(EXIT_FAILURE);
	}
	execve(redirect->argv[0], redirect->argv, NULL);
	error_exit("execve", shell);
}

static void	execute_command_shell(t_redirect *redirect_array,
	int i, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (redirect_array[i].infile.fd == -1)
		redirect_array[i].infile.fd = STDIN_FILENO;
	if (redirect_array[i].outfile.fd == -1)
		redirect_array[i].outfile.fd = STDOUT_FILENO;
	if (pid == 0)
	{
		if (redirect_array[i].infile.fd != STDIN_FILENO)
			handle_child(&redirect_array[i], shell);
	}
	else if (pid < 0)
		error_exit("fork", shell);
	else
		waitpid(pid, &status, 0);
}

void	execute_redirection(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmds)
	{
		shell->redirect_array[i].argv[0] = check_command_existence
			(shell->redirect_array[i].argv[0], shell->env);
		printf("command: %s\n", shell->redirect_array[i].argv[0]);
		i++;
	}
	i = 0;
	while (i < shell->nb_cmds)
	{
		execute_command_shell(shell->redirect_array, i, shell);
		i++;
	}
}
