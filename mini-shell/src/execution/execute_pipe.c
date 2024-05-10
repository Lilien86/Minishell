#include "../minishell.h"

#define READ_END 0
#define WRITE_END 1
#define MAX_PIPES 10


void	handle_wait(t_minishell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->nb_cmds)
	{
		wait(&status);
		i++;
	}
}

void	ft_exec(t_redirect *redirect_array, int index, t_minishell *shell, int pipes[MAX_PIPES][2])
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
		if (check_builtins(redirect_array[index].argv[0]) == 1)
		{
			execute_builtins(ft_strlen_map(redirect_array[index].argv), redirect_array[index].argv, shell);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execve(redirect_array[index].argv[0], redirect_array[index].argv, shell->env);
			perror("execve");
			exit(EXIT_FAILURE);
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
		if (shell->redirect_array[i].infile.fd == -2
			|| shell->redirect_array[i].outfile.fd == -2)
			return ;
		if (check_builtins(shell->redirect_array[i].argv[0]) != 1)
		{
			shell->redirect_array[i].argv[0] = check_command_existence(
					shell->redirect_array[i].argv[0], shell->env);
		}
		i++;
	}
	i = 0;
	while (i < shell->nb_cmds)
	{
		ft_exec(shell->redirect_array, i, shell, pipes);
		close(shell->redirect_array[i].infile.fd);
		close(shell->redirect_array[i].outfile.fd);
		i++;
	}
	handle_wait(shell);
}
