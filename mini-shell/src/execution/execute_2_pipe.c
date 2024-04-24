#include "../minishell.h"

void	handle_new_pipe(t_minishell *shell, t_pipe *the_pipe, int i)
{
	if (pipe(the_pipe->pipefd) == -1)
		error_exit("pipe", shell);
	shell->redirect_array[i].outfile.fd = the_pipe->pipefd[1];
	the_pipe->prev_pipe[0] = the_pipe->pipefd[0];
	the_pipe->prev_pipe[1] = the_pipe->pipefd[1];
	the_pipe->pipe_count = 1;
}

void	handle_while(int i, t_minishell *shell, t_pipe *the_pipe)
{
	while (i < shell->nb_cmds)
	{
		if (i > 0)
		{
			shell->redirect_array[i].infile.fd = the_pipe->prev_pipe[0];
			if (i == shell->nb_cmds - 1)
			{
				shell->redirect_array[i].outfile.fd = STDOUT_FILENO;
			}
			else
				handle_new_pipe(shell, the_pipe, i);
		}
		else
		{
			if (shell->nb_cmds == 1)
				shell->redirect_array[i].outfile.fd = STDOUT_FILENO;
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

void	execute_command_shell_2(t_minishell *shell)
{
	t_pipe	pipe_info;
	int		i;

	i = 0;
	pipe_info.pipe_count = 0;
	while (i < shell->nb_cmds)
	{
		if (check_builtins(shell->redirect_array[i].argv[0]) == 0)
			shell->redirect_array[i].argv[0] = check_command_existence
				(shell->redirect_array[i].argv[0], shell->env);
		i++;
	}
	i = 0;
	handle_while(i, shell, &pipe_info);
	if (pipe_info.pipe_count > 0)
	{
		close(pipe_info.prev_pipe[0]);
		close(pipe_info.prev_pipe[1]);
	}
}
