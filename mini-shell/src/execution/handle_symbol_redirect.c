/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:14 by lauger            #+#    #+#             */
/*   Updated: 2024/04/12 13:35:19 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input_redirect(t_minishell *shell, t_token *current, int *i)
{
	if (current->next == NULL)
	{
		ft_printf("Error:\nno file specified\n");
		shell->exit_status = 1;
		return ;
	}
	shell->redirect_array[*i].infile.name = current->next->value;
	check_file(&shell->redirect_array[*i].infile, 0, shell);
}

void	handle_output_redirect(t_minishell *shell,
	t_token *current, int *i, int is_double_redirect)
{
	if (current->next == NULL)
	{
		ft_printf("Error:\nno file specified\n");
		shell->exit_status = 1;
		return ;
	}
	shell->redirect_array[*i].outfile.name = current->next->value;
	check_file(&shell->redirect_array[*i].outfile, is_double_redirect, shell);
	//shell->tokens = current->next->next;
}

void	handle_heredoc(t_minishell *shell, t_token *current, int *i)
{
	here_doc(current, shell, *i);
}

void	handle_pipe(t_minishell *shell, int *i)
{
	(*i)++;
	shell->redirect_array[*i].infile.name = NULL;
	shell->redirect_array[*i].infile.fd = -1;
	shell->redirect_array[*i].outfile.name = NULL;
	shell->redirect_array[*i].outfile.fd = -1;
	shell->redirect_array[*i].argv = NULL;
}
