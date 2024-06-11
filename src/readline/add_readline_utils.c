/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_readline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:53:02 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 10:19:09 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_read(t_minishell *shell)
{
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens != NULL)
	{
		free_tokens(&(shell->tokens));
		shell->tokens = NULL;
	}
	if (shell->redirect_array != NULL)
	{
		free_redirect_array(shell, shell->nb_cmds);
		shell->redirect_array = NULL;
	}
	if (shell->tab_here_doc != NULL)
	{
		free_tab_here_doc(shell->tab_here_doc, shell->nb_cmds);
		shell->tab_here_doc = NULL;
	}
}

int	read_input(t_minishell *shell)
{
	int	local_exit_status;

	while (1)
	{
		if (shell->input != NULL)
		{
			free(shell->input);
			shell->input = NULL;
		}
		shell->input = readline("minishell > ");
		if (shell->input == NULL)
		{
			local_exit_status = shell->exit_status;
			free_minishell(shell);
			ft_printf("exit\n");
			exit(local_exit_status);
		}
		handle_input(shell);
		free_read(shell);
	}
	return (0);
}

void	handle_input(t_minishell *shell)
{
	if (ft_strcmp(shell->input, "") == 0)
		return ;
	process_input(shell);
}
