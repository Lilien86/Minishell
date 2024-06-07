/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:14 by lauger            #+#    #+#             */
/*   Updated: 2024/06/07 16:33:39 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input_redirect(t_minishell *cpy, t_token *current,
	int *i, t_minishell *shell)
{
	if (current->next == NULL || check_valid_redirect(current->next) == 1)
	{
		ft_putstr_fd("minishell: Error: syntax error near"
			" unexpected token `newline' `<'\n", 2);
		shell->exit_status = 2;
		shell->redirect_array[0].infile.fd = -2;
		return ;
	}
	cpy->redirect_array[*i].infile.name = current->next->value;
	open_file_in(&cpy->redirect_array[*i].infile, *i, shell);
}

void	handle_output_redirect(t_minishell *cpy, t_token *current, int *i,
			t_minishell *shell)
{
	if (current->next == NULL || check_valid_redirect(current->next) == 1)
	{
		ft_putstr_fd("minishell: Error: syntax error near"
			" unexpected token `newline' `>'\n", 2);
		shell->exit_status = 2;
		shell->redirect_array[0].infile.fd = -2;
		return ;
	}
	cpy->redirect_array[*i].outfile.name = current->next->value;
	open_file_out(&cpy->redirect_array[*i].outfile, cpy, *i, shell);
}

void	handle_output_redirect_append(t_minishell *cpy,
	t_token *current, int *i, t_minishell *shell)
{
	if (current->next == NULL || check_valid_redirect(current->next) == 1)
	{
		ft_putstr_fd("minishell: Error: syntax error near"
			" unexpected token `newline' `>>'\n", 2);
		shell->exit_status = 2;
		shell->redirect_array[0].infile.fd = -2;
		return ;
	}
	cpy->redirect_array[*i].outfile.name = current->next->value;
	open_file_out_append(&cpy->redirect_array[*i].outfile, cpy, *i, shell);
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
