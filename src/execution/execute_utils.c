/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:11:06 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 11:24:42 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_builtins(t_minishell *shell,
				t_redirect *redirect_array, int index)
{
	close_fd_pipe(shell->pipes);
	execute_builtins(ft_strlen_map(redirect_array[index].argv),
		redirect_array[index].argv, shell);
	free_minishell(shell);
	exit(EXIT_SUCCESS);
}

static void	handle_command(t_minishell *shell,
				t_redirect *redirect_array, int index)
{
	close_fd_pipe(shell->pipes);
	if (access(redirect_array[index].argv[0], F_OK) == 0)
		execve(redirect_array[index].argv[0],
			redirect_array[index].argv, shell->env);
	if (is_file(redirect_array[index].argv[0]) == 0)
	{
		ft_putstr_fd("minishell: Is a directory:"
			" You need to use a command\n", 2);
		exit(126);
	}
	free_minishell(shell);
	ft_putstr_fd("minishell: command not found\n", 2);
	exit(127);
}

void	handle_execute(t_minishell *shell, t_redirect *redirect_array,
	int index)
{
	if (redirect_array[index].argv != NULL
		&& check_builtins(redirect_array[index].argv[0]) == 1)
	{
		handle_builtins(shell, redirect_array, index);
	}
	else if (redirect_array[index].argv != NULL
		|| redirect_array[index].argv[0][0] == '$')
	{
		handle_command(shell, redirect_array, index);
	}
	exit(EXIT_FAILURE);
}
