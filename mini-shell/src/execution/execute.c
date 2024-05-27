#include "../minishell.h"

int	handle_wait(t_minishell *shell)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	pid;

	i = 0;
	last_status = shell->exit_status;
	while (i < shell->nb_cmds)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			perror("waitpid");
			break ;
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = WTERMSIG(status);
		i++;
	}
	return (last_status);
}

void	handle_dup_close(int index, t_redirect *redirect_array,
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
		close(pipes[index][READ_END]);
		close(pipes[index][WRITE_END]);
	}
	if (index > 0)
	{
		dup2(pipes[index - 1][READ_END], STDIN_FILENO);
		close(pipes[index - 1][WRITE_END]);
		close(pipes[index - 1][READ_END]);
	}
	if (redirect_array[index].outfile.fd != -1)
	{
		dup2(redirect_array[index].outfile.fd, STDOUT_FILENO);
		close(redirect_array[index].outfile.fd);
	}
	if (redirect_array[index].infile.fd != -1)
	{
		dup2(redirect_array[index].infile.fd, STDIN_FILENO);
		close(redirect_array[index].infile.fd);
	}
}

void	ft_exec(t_redirect *redirect_array, int index, t_minishell *shell,
	int pipes[MAX_PIPES][2])
{
	pid_t	pid;

	if (index < shell->nb_cmds - 1)
		pipe(pipes[index]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		handle_dup_close(index, redirect_array, shell, pipes);
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
			execve(redirect_array[index].argv[0], redirect_array[index].argv,
				shell->env);
			ft_putstr_fd("minishell: command not found", 2);
			free_minishell(shell);
			exit(127);
		}
	}
	else
	{
		if (index < shell->nb_cmds - 1)
			close(pipes[index][WRITE_END]);
	}
}

void	execute_command_shell(t_minishell *shell)
{
	int		i;
	int		pipes[MAX_PIPES][2];

	i = 0;
	while (i < shell->nb_cmds)
	{
		if (shell->redirect_array[i].argv != NULL
			&& check_builtins(shell->redirect_array[i].argv[0]) != 1)
		{
			shell->redirect_array[i].argv[0] = check_command_existence(
					shell->redirect_array[i].argv[0], shell->env);
		}
		i++;
	}
	i = 0;
	while (i < shell->nb_cmds)
	{
		if (shell->redirect_array[i].argv != NULL)
			ft_exec(shell->redirect_array, i, shell, pipes);
		i++;
	}
	shell->exit_status = handle_wait(shell);
	//printf("exit status: %d\n", shell->exit_status);
}
