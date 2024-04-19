#include "../minishell.h"

void	handle_child(t_redirect *redirect, t_minishell *shell)
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

void	execute_single_command(t_redirect *redirect, t_minishell *shell)
{
	pid_t	pid;
	int		status;

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
		waitpid(pid, &status, 0);
		close(redirect->infile.fd);
		close(redirect->outfile.fd);
	}
}
