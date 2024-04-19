#include "../minishell.h"

typedef struct s_pipe
{
	int	pipefd[2];
	int	prev_pipe[2];
	int	pipe_count;
}	t_pipe;

/*
void	execute_command_shell_2(t_minishell *shell)
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
	while (i < shell->nb_cmds)
	{
		if (i > 0)
		{
			shell->redirect_array[i].infile.fd = prev_pipe[0];
			if (i == shell->nb_cmds - 1)
			{
				shell->redirect_array[i].outfile.fd = STDOUT_FILENO;
			}
			else
			{
				if (pipe(pipefd) == -1)
					error_exit("pipe", shell);
				shell->redirect_array[i].outfile.fd = pipefd[1];
				prev_pipe[0] = pipefd[0];
				prev_pipe[1] = pipefd[1];
				pipe_count = 1;
			}
		}
		else
		{
			if (shell->nb_cmds == 1)
				shell->redirect_array[i].outfile.fd = STDOUT_FILENO;
			else
			{
				if (pipe(pipefd) == -1)
					error_exit("pipe", shell);
				shell->redirect_array[i].outfile.fd = pipefd[1];
				prev_pipe[0] = pipefd[0];
				prev_pipe[1] = pipefd[1];
				pipe_count = 1;
			}
		}
		execute_single_command(&shell->redirect_array[i], shell);
		i++;
	}
	if (pipe_count > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
}*/

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
		execute_single_command(&shell->redirect_array[i], shell);
		i++;
	}
}

void execute_command_shell_2(t_minishell *shell)
{
	t_pipe	pipe_info;
	int		i;

	i = 0;
	pipe_info.pipe_count = 0;
	while (i < shell->nb_cmds)
	{
		shell->redirect_array[i].argv[0] = check_command_existence(shell->redirect_array[i].argv[0], shell->env);
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
