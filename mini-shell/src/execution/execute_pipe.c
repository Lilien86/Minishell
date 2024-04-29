#include "../minishell.h"

void	handle_new_pipe(t_minishell *shell, t_pipe *the_pipe, int i)
{
	if (pipe(the_pipe->pipefd) == -1)
		error_exit("pipe", shell);
	the_pipe->prev_pipe[0] = the_pipe->pipefd[0];
	the_pipe->prev_pipe[1] = the_pipe->pipefd[1];
	shell->redirect_array[i].outfile.fd = the_pipe->pipefd[1];
	the_pipe->pipe_count = 1;
}

// void handle_new_pipe(t_minishell *shell, t_pipe *the_pipe, int i)
// {
// 	if (pipe(the_pipe->pipefd) == -1)
// 		error_exit("pipe", shell);
// 	shell->redirect_array[i].outfile.fd = the_pipe->pipefd[1];
// 	the_pipe->prev_pipe[0] = the_pipe->pipefd[0];
// 	the_pipe->prev_pipe[1] = the_pipe->pipefd[1];
// 	the_pipe->pipe_count = 1;

// 	// Vérifier si le fd de lecture du pipe est valide avant de l'utiliser avec dup2
// 	if (the_pipe->pipefd[0]!= -1)
// 	{
// 		if (dup2(the_pipe->pipefd[0], STDIN_FILENO) == -1)
// 			error_exit("dup2", shell);
// 		close(the_pipe->pipefd[1]);
// 	}
// 	else
// 		error_exit("Invalid pipe fd", shell);
// }

void	handle_while(int i, t_minishell *shell, t_pipe *the_pipe)
{
	printf("par pid: %d\n", getpid());
	while (i < shell->nb_cmds)
	{
		if (i > 0)
		{
			if (shell->redirect_array[i].infile.fd == -1)
				shell->redirect_array[i].infile.fd = the_pipe->prev_pipe[0];
			if (i == shell->nb_cmds - 1)
			{
				if (shell->redirect_array[i].outfile.fd == -1)
					shell->redirect_array[i].outfile.fd = STDOUT_FILENO;
			}
			else
				handle_new_pipe(shell, the_pipe, i);
		}
		else
		{
			if (shell->nb_cmds == 1)
			{
				if (shell->redirect_array[i].infile.fd == -1)
					shell->redirect_array[i].infile.fd = STDIN_FILENO;
				if (shell->redirect_array[i].outfile.fd == -1)
					shell->redirect_array[i].outfile.fd = STDOUT_FILENO;
			}
			else
				handle_new_pipe(shell, the_pipe, i);
		}
		//printf("count--->%d\n\n", the_pipe->pipe_count);
		//printf("prev_pipe[lecture]--->%d\n", the_pipe->prev_pipe[0]);
		//printf("prev_pipe[ecriture]--->%d\n\n", the_pipe->prev_pipe[1]);
		//printf("pipefd[lecture]--->%d\n", the_pipe->pipefd[0]);
		//printf("pipefd[ecriture]--->%d\n\n", the_pipe->pipefd[1]);
		execute_single_command(&shell->redirect_array[i], shell);
		i++;
	}
}

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

void	execute_command_shell_2(t_minishell *shell)
{
	t_pipe	pipe_info;
	int		i;

	i = 0;
	pipe_info.pipe_count = 0;
	while (i < shell->nb_cmds)
	{
		if (check_builtins(shell->redirect_array[i].argv[0]) != 1)
		{
			shell->redirect_array[i].argv[0] = check_command_existence
				(shell->redirect_array[i].argv[0], shell->env);
		}
		i++;
	}
	i = 0;
	handle_while(i, shell, &pipe_info);
	handle_wait(shell);
	if (pipe_info.pipe_count > 0)
	{
		close(pipe_info.prev_pipe[0]);
		close(pipe_info.prev_pipe[1]);
	}
}
