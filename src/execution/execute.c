/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:47:29 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/10 20:34:31 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (shell->exit_status != 2)
			execute_commands(shell, i, pipes);
		shell->exit_status = handle_wait(shell);
	}
}
