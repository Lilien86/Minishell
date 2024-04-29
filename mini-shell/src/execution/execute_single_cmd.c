#include "../minishell.h"

void	handle_child(t_redirect *redirect, t_minishell *shell)
{
	printf("in: %d\n out: %d\n", redirect->infile.fd, redirect->outfile.fd);
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
	if (check_builtins(redirect->argv[0]))
	{
		execute_builtins(shell);
		exit(shell->exit_status);
	}
	else
	{
		if (access(redirect->argv[0], X_OK) == -1)
		{
			exit(EXIT_FAILURE);
		}
		dprintf(2, "pid: %d\n", getpid());
		execve(redirect->argv[0], redirect->argv, NULL);
		error_exit("execve", shell);
	}
}

void	execute_single_command(t_redirect *redirect, t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (redirect->infile.fd == -1)
		redirect->infile.fd = STDIN_FILENO;
	if (redirect->outfile.fd == -1)
		redirect->outfile.fd = STDOUT_FILENO;
	if (pid == 0)
		handle_child(redirect, shell);
	else if (pid < 0)
		error_exit("fork", shell);
	else
	{
		//if (redirect->infile.fd != STDIN_FILENO)
		close(redirect->infile.fd);
		//if (redirect->outfile.fd != STDOUT_FILENO)
		close(redirect->outfile.fd);
	}
}
