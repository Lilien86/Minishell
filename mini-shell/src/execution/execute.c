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
			//ft_putstr_fd("Error: During execution\n", STDERR_FILENO);
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

static void	init_pipes(int pipes[MAX_PIPES][2])
{
	int	i;

	i = 0;
	while (i < MAX_PIPES)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
}

void	execute_command_shell(t_minishell *shell)
{
	int		i;
	int		pipes[MAX_PIPES][2];

	i = 0;
	init_pipes(pipes);
	if (shell->nb_cmds - 1 < MAX_PIPES)
	{
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
			if (shell->redirect_array[i].argv != NULL
				&& shell->redirect_array[i].argv[0] != NULL)
				ft_exec(shell->redirect_array, i, shell, pipes);
			i++;
		}
		shell->exit_status = handle_wait(shell);
	}
	//printf("exit status: %d\n", shell->exit_status);
}
