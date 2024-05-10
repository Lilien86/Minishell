#include "../minishell.h"

void	execute_execve(t_redirect *redirect, t_minishell *shell)
{
	if (access(redirect->argv[0], X_OK) == -1)
	{
		exit(EXIT_FAILURE);
	}
	execve(redirect->argv[0], redirect->argv, shell->env);
	error_exit("execve", shell);
}

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
	if (check_builtins(redirect->argv[0]))
	{
		execute_builtins(ft_strlen_map(redirect->argv), redirect->argv, shell);
		exit(shell->exit_status);
	}
	else
		execute_execve(redirect, shell);
}

void	execute_command(t_redirect *redirect, t_minishell *shell)
{
	pid_t	pid;

	if (redirect->infile.fd == -1)
		redirect->infile.fd = STDIN_FILENO;
	if (redirect->outfile.fd == -1)
		redirect->outfile.fd = STDOUT_FILENO;
	pid = fork();
	if (pid == 0)
		handle_child(redirect, shell);
	else if (pid < 0)
		error_exit("fork", shell);
	else if (shell->nb_cmds != 1)
	{
		if (redirect->infile.fd != STDIN_FILENO
			&& redirect->infile.fd != STDOUT_FILENO)
			close(redirect->infile.fd);
		if (redirect->outfile.fd != STDIN_FILENO
			&& redirect->outfile.fd != STDOUT_FILENO)
			close(redirect->outfile.fd);
	}
}
