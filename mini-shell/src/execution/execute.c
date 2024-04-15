/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:21:10 by lauger            #+#    #+#             */
/*   Updated: 2024/04/15 13:53:55 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_exit(char *message, t_minishell *shell)
{
	perror(message);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
}

// static void	execute_command_shell(t_redirect *redirect_array,
// 	int i, t_minishell *shell)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (redirect_array[i].infile.fd == -1)
// 		redirect_array[i].infile.fd = STDIN_FILENO;
// 	if (redirect_array[i].outfile.fd == -1)
// 		redirect_array[i].outfile.fd = STDOUT_FILENO;
// 	if (pid == 0)
// 	{
// 		if (redirect_array[i].infile.fd != STDIN_FILENO)
// 		{
// 			if (dup2(redirect_array[i].infile.fd, STDIN_FILENO) == -1)
// 				error_exit("dup2", shell);
// 			close(redirect_array[i].infile.fd);
// 		}
// 		if (redirect_array[i].outfile.fd != STDOUT_FILENO)
// 		{
// 			if (dup2(redirect_array[i].outfile.fd, STDOUT_FILENO) == -1)
// 				error_exit("dup2", shell);
// 			close(redirect_array[i].outfile.fd);
// 		}
// 		if (execve(redirect_array[i].argv[0], redirect_array[i].argv, NULL) == -1)
// 		error_exit("execve", shell);
// 	}
// 	else if (pid < 0)
// 		error_exit("fork", shell);
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// }

static void execute_command_shell(t_redirect *redirect_array, int i, t_minishell *shell) {
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) {
		// Processus enfant
		if (redirect_array[i].infile.name != NULL) {
			// Redirection de l'entrée à partir du fichier spécifié
			int infile_fd = open(redirect_array[i].infile.name, O_RDONLY);
			if (infile_fd == -1)
				error_exit("open", shell);
			if (dup2(infile_fd, STDIN_FILENO) == -1)
				error_exit("dup2", shell);
			close(infile_fd);
		}

		// Redirection de la sortie
		if (redirect_array[i].outfile.fd != STDOUT_FILENO) {
			if (dup2(redirect_array[i].outfile.fd, STDOUT_FILENO) == -1)
				error_exit("dup2", shell);
		}

		// Exécution de la commande
		if (execvp(redirect_array[i].argv[0], redirect_array[i].argv) == -1)
			error_exit("execve", shell);
	} else if (pid < 0) {
		// Erreur lors du fork
		error_exit("fork", shell);
	} else {
		// Processus parent
		waitpid(pid, &status, 0);
	}
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
