#include "../minishell.h"

static void error_exit(char *message, t_minishell *shell)
{
	perror(message);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
}


#include <unistd.h>

static void	execute_single_command(t_redirect *redirect, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (redirect->infile.fd == -1)
		redirect->infile.fd = STDIN_FILENO;
	if (redirect->outfile.fd == -1)
		redirect->outfile.fd = STDOUT_FILENO;
	if (pid == 0)
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
			ft_printf("Error: %s is not executable or does not exist.\n", redirect->argv[0]);
			exit(EXIT_FAILURE);
		}
		execve(redirect->argv[0], redirect->argv, NULL);
		error_exit("execve", shell);
	}
	else if (pid < 0)
		error_exit("fork", shell);
	else
	{
		waitpid(pid, &status, 0);
		close(redirect->infile.fd);
		close(redirect->outfile.fd);
	}
	
}


void	execute_command_shell_2(t_redirect *redirect_array, int nb_cmds, t_minishell *shell)
{
	int pipefd[2];
	int i = 0;
	int prev_pipe[2];
	int pipe_count = 0;

	while (i < shell->nb_cmds)
	{
		shell->redirect_array[i].argv[0] = check_command_existence(shell->redirect_array[i].argv[0], shell->env);
		i++;
	}
	i = 0;
	while (i < nb_cmds)
	{
		if (i > 0)
		{
			redirect_array[i].infile.fd = prev_pipe[0];
			if (i == nb_cmds - 1)
			{
				redirect_array[i].outfile.fd = STDOUT_FILENO;
			}
			else
			{
				if (pipe(pipefd) == -1)
					error_exit("pipe", shell);
				redirect_array[i].outfile.fd = pipefd[1];
				prev_pipe[0] = pipefd[0];
				prev_pipe[1] = pipefd[1];
				pipe_count = 1;
			}
		}
		else
		{
			if (nb_cmds == 1)
				redirect_array[i].outfile.fd = STDOUT_FILENO;
			else
			{
				if (pipe(pipefd) == -1)
					error_exit("pipe", shell);
				redirect_array[i].outfile.fd = pipefd[1];
				prev_pipe[0] = pipefd[0];
				prev_pipe[1] = pipefd[1];
				pipe_count = 1;
			}
		}
		execute_single_command(&redirect_array[i], shell);
		i++;
	}
	if (pipe_count > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
}
