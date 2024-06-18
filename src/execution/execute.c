/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:47:29 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 11:35:31 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_only(const char *str, const char *allowed)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	while (str[i] != '\0')
	{
		found = 0;
		j = 0;
		while (allowed[j] != '\0')
		{
			if (str[i] == allowed[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			return (0);
		i++;
	}
	return (1);
}

int	check_invalid_folder(char *folder, t_minishell *shell)
{
	if (!folder)
		return (0);
	if (folder && (ft_strcmp(folder, "./") == 0
			|| ft_strcmp(folder, "../") == 0
			|| ft_strcmp(folder, ".") == 0
			|| ft_strcmp(folder, "..") == 0
			|| contains_only(folder, "./") == 1))
	{
		shell->exit_status = 126;
		return (1);
	}
	return (0);
}

static void	check_commands(t_minishell *shell, int i)
{
	while (i < shell->nb_cmds)
	{
		if (shell->redirect_array[i].argv != NULL
			&& check_builtins(shell->redirect_array[i].argv[0]) != 1)
		{
			if (check_invalid_folder(
					shell->redirect_array[i].argv[0], shell) == 0)
				shell->redirect_array[i].argv[0] = check_command_existence(
						shell->redirect_array[i].argv[0], shell->env);
			if (shell->redirect_array[i].argv[0] == NULL)
			{
				ft_putstr_fd("minishell: command not found\n", 2);
				shell->exit_status = 127;
			}
		}
		i++;
	}
}

static void	execute_commands(t_minishell *shell, int i, int pipes[MAX_PIPES][2])
{
	while (i < shell->nb_cmds)
	{
		if (shell->redirect_array[i].argv != NULL
			&& shell->redirect_array[i].argv[0] != NULL
			&& check_invalid_folder(
				shell->redirect_array[i].argv[0], shell) == 0)
			ft_exec(shell->redirect_array, i, shell, pipes);
		if (shell->redirect_array[i].argv != NULL && check_invalid_folder(
				shell->redirect_array[i].argv[0], shell) == 1)
			ft_putstr_fd("minishell: syntax error: unexpected path\n", 2);
		i++;
	}
}

void	execute_command_shell(t_minishell *shell)
{
	int		i;

	i = 0;
	init_pipes(shell->pipes);
	if (shell->nb_cmds - 1 < MAX_PIPES)
	{
		check_commands(shell, i);
		if (shell->exit_status != 2)
		{
			execute_commands(shell, i, shell->pipes);
			if (shell->redirect_array[i].argv != NULL
				&& shell->redirect_array[i].argv[0] != NULL
				&& check_invalid_folder(
					shell->redirect_array[0].argv[0], shell) == 0)
				shell->exit_status = handle_wait(shell);
		}
	}
}
