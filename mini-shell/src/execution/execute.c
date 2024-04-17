/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:21:10 by lauger            #+#    #+#             */
/*   Updated: 2024/04/16 11:23:12 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_exit(char *message, t_minishell *shell)
{
	perror(message);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
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
		{
			if (dup2(redirect_array[i].infile.fd, STDIN_FILENO) == -1)
			{
				error_exit("dup2", shell);
				exit(EXIT_FAILURE);
			}
			close(redirect_array[i].infile.fd);
		}
		if (redirect_array[i].outfile.fd != STDOUT_FILENO)
		{
			if (dup2(redirect_array[i].outfile.fd, STDOUT_FILENO) == -1)
			{
				error_exit("dup2", shell);
				exit(EXIT_FAILURE);
			}
			close(redirect_array[i].outfile.fd);
		}
		if (execve(redirect_array[i].argv[0], redirect_array[i].argv, NULL) == -1)
			error_exit("execve", shell);
	}
	else if (pid < 0)
		error_exit("fork", shell);
	else
		waitpid(pid, &status, 0);
}

void execute_redirection(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmds)
	{
		shell->redirect_array[i].argv[0] = check_command_existence(shell->redirect_array[i].argv[0], shell->env);
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
