/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:47:29 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/07 16:09:06 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	check_commands(t_minishell *shell, int i)
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
}

void	check_invalid_folder(char *folder, t_minishell *shell)
{
	if (folder && (ft_strcmp(folder, "./") == 0
			|| ft_strcmp(folder, "../") == 0
			|| ft_strcmp(folder, ".") == 0
			|| ft_strcmp(folder, "..") == 0))
	{
		ft_putstr_fd("minishell: syntax error: unexpected path\n", 2);
		shell->exit_status = 126;
	}
}

static void	execute_commands(t_minishell *shell, int i, int pipes[MAX_PIPES][2])
{
	while (i < shell->nb_cmds)
	{
		if (shell->redirect_array[i].argv != NULL
			&& shell->redirect_array[i].argv[0] != NULL
			&& is_file(shell->redirect_array[0].argv[0]) != 0)
			ft_exec(shell->redirect_array, i, shell, pipes);
		else if (is_file(shell->redirect_array[0].argv[0]) == 0)
			check_invalid_folder(shell->redirect_array[0].argv[0], shell);
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
		check_commands(shell, i);
		execute_commands(shell, i, pipes);
		shell->exit_status = handle_wait(shell);
	}
	//printf("exit status: %d\n", shell->exit_status);
}
