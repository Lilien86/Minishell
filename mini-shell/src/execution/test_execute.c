#include "../minishell.h"

static void error_exit(char *message, t_minishell *shell)
{
	perror(message);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
}

static void execute_single_command(char **argv, int in_fd, int out_fd, t_minishell *shell)
{
	pid_t pid = fork();
	if (pid == -1)
		error_exit("fork", shell);
	else if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1)
				error_exit("dup2", shell);
			close(in_fd);
		}
		// Redirection de la sortie
		if (out_fd != STDOUT_FILENO)
		{
			if (dup2(out_fd, STDOUT_FILENO) == -1)
				error_exit("dup2", shell);
			close(out_fd);
		}
		// Exécution de la commande
		if (execvp(argv[0], argv) == -1)
			error_exit("execvp", shell);
	}
	else
	{
		// Processus parent
		waitpid(pid, NULL, 0);
	}
}

static int create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return -1;
	}
	return 0;
}

static void close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

static void execute_command_shell(t_redirect *redirect_array, int nb_cmds, t_minishell *shell)
{
	int in_fd = STDIN_FILENO;
	int out_fd;
	int pipefd[2];
	int i = 0;

	while (i < nb_cmds)
	{
		if (i < nb_cmds - 1) //classic type
		{
			if (create_pipe(pipefd) == -1)
				return;
			out_fd = pipefd[1]; // Utilise l'extrémité d'écriture du tube
		}
		else //last cmd
			out_fd = STDOUT_FILENO;
		execute_single_command(redirect_array[i].argv, in_fd, out_fd, shell);
		// Ferme le tube si ce n'est pas la dernière commande
		if (i < nb_cmds - 1)
		{
			close_pipe(pipefd);
			in_fd = pipefd[0]; // Utilise l'extrémité de lecture du tube pour l'entrée de la prochaine commande
		}
		i++;
	}
}