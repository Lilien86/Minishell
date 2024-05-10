/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:06:14 by lauger            #+#    #+#             */
/*   Updated: 2024/05/08 09:47:25 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input_redirect(t_minishell *cpy, t_token *current, int *i, t_minishell *shell)
{
	if (current->next == NULL)
	{
		ft_putstr_fd("minishell: Error: parse error near\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[0].infile.fd = -2;
		return ;
	}
	cpy->redirect_array[*i].infile.name = current->next->value;
	check_file(&cpy->redirect_array[*i].infile, 0, cpy, 0);
}

void	handle_output_redirect(t_minishell *cpy,
	t_token *current, int *i, int is_double_redirect, t_minishell *shell)
{
	if (current->next == NULL)
	{
		ft_putstr_fd("minishell: Error: parse error near\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[0].infile.fd = -2;
		return ;
	}
	cpy->redirect_array[*i].outfile.name = current->next->value;
	check_file(
		&cpy->redirect_array[*i].outfile, is_double_redirect, cpy, 1);
}

// void	handle_heredoc(t_minishell *shell, t_token *current, int *i)
// {
// 	if (current->next == NULL)
// 	{
// 		ft_putstr_fd("minishell: Error: parse error near\n", 2);
// 		shell->exit_status = 1;
// 		shell->redirect_array[0].infile.fd = -2;
// 		return ;
// 	}
// 	here_doc(current, shell, *i);
// }

void	handle_pipe(t_minishell *shell, int *i)
{
	(*i)++;
	shell->redirect_array[*i].infile.name = NULL;
	shell->redirect_array[*i].infile.fd = -1;
	shell->redirect_array[*i].outfile.name = NULL;
	shell->redirect_array[*i].outfile.fd = -1;
	shell->redirect_array[*i].argv = NULL;
}
