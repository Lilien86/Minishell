/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:56:00 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/30 09:56:02 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_minishell_part1(t_minishell *shell)
{
	if (shell->env)
	{
		ft_free_tab(shell->env);
		shell->env = NULL;
	}
	free_tokens(&(shell->tokens));
	shell->tokens = NULL;
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free_history(shell->history);
	*shell->history = NULL;
}

static void	free_minishell_part2(t_minishell *shell)
{
	if (shell->redirect_array)
	{
		free_redirect_array(shell, shell->nb_cmds);
		shell->redirect_array = NULL;
	}
	if (shell->tab_here_doc)
	{
		free_tab_here_doc(shell->tab_here_doc, shell->nb_cmds);
		shell->tab_here_doc = NULL;
	}
	if (shell != NULL)
	{
		free(shell);
		shell = NULL;
	}
}

void	free_minishell(t_minishell *shell)
{
	if (!shell)
		return ;
	free_minishell_part1(shell);
	free_minishell_part2(shell);
}
