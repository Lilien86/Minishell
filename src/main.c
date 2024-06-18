/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:00:09 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 14:13:28 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;
	int			exit_status;

	rl_catch_signals = 0;
	exit_status = 0;
	(void)argc;
	(void)argv;
	shell = init_minishell(envp);
	if (!shell)
		return (1);
	init_signal_handlers();
	set_pwd_if_not_defined(&shell->env);
	increment_shlvl(&shell->env);
	read_input(shell);
	exit_status = shell->exit_status;
	free_minishell(shell);
	return (exit_status);
}
