#include "../minishell.h"

static void error_exit(char *message, t_minishell *shell)
{
	perror(message);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
}

// static void close_pipe(int pipefd[2])
// {
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// }

static void	execute_single_command(t_redirect *redirect, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	printf("\n1");
	pid = fork();
	if (pid == 0)
	{
		if (redirect->infile.fd != STDIN_FILENO)
		{
			if (dup2(redirect->infile.fd, STDIN_FILENO) == -1)
			{
				error_exit("dup2", shell);
				exit(EXIT_FAILURE);
			}
			close(redirect->infile.fd);
		}
		if (redirect->outfile.fd != STDOUT_FILENO)
		{
			if (dup2(redirect->outfile.fd, STDOUT_FILENO) == -1)
			{
				error_exit("dup2", shell);
				exit(EXIT_FAILURE);
			}
			close(redirect->outfile.fd);
		}
		if (access(redirect->argv[0], X_OK) == -1)
		{
			ft_printf("Error: %s is not executable or does not exist.\n", redirect->argv[0]);
			exit(EXIT_FAILURE);
		}
		if (execve(redirect->argv[0], redirect->argv, NULL) == -1)
		{
			error_exit("execve", shell);
		}
	}
	else if (pid < 0)
		error_exit("fork", shell);
	else
		waitpid(pid, &status, 0);
}

void	execute_command_shell_2(t_redirect *redirect_array, int nb_cmds, t_minishell *shell)
{
	int		pipefd[2];
	int		i;

	i = 0;
	while (i < shell->nb_cmds)
	{
		shell->redirect_array[i].argv[0] = check_command_existence(shell->redirect_array[i].argv[0], shell->env);
		//printf("command: %s\n", shell->redirect_array[i].argv[0]);
		i++;
	}
	i = 0;
	if (nb_cmds == 1)
	{
		execute_single_command(&redirect_array[0], shell);
		return ;
	}
	while (i < nb_cmds)
	{
		if (i < nb_cmds - 1)
		{
			if (pipe(pipefd) == -1)
			{
				error_exit("pipe", shell);
				return;
			}
			redirect_array[i].outfile.fd = pipefd[1]; // Utilise l'extrémité d'écriture du tube
		}
		if (i > 0)
		{
			redirect_array[i].infile.fd = pipefd[0]; // Utilise l'extrémité de lecture du tube précédent
		}

		execute_single_command(&redirect_array[i], shell);

		if (i < nb_cmds - 1)
		{
			close(pipefd[0]); // Ferme l'extrémité de lecture du tube actuel
			close(pipefd[1]); // Ferme l'extrémité d'écriture du tube actuel
		}

		i++;
	}
}
