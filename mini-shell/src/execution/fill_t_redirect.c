/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:48:37 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/05 09:22:20 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_redirect_array(t_minishell *shell)
{
	shell->nb_cmds = counter_cmds(shell->tokens);
	shell->redirect_array = ft_calloc((size_t)shell->nb_cmds,
			sizeof(t_redirect));
	if (shell->redirect_array == NULL)
	{
		perror("Error malloc data_array");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	return (1);
}

static void	handle_heredoc(*i, t_minishell *shell,
	int *here_doc_available, int *id_here_doc)
{
	if (shell->cpy.tokens->type == TOKEN_HEREDOC && *here_doc_available == 0)
	{
		if (cpy.tokens->next == NULL
			|| check_valid_redirect(cpy.tokens->next) == 1)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			shell->exit_status = 2;
			shell->redirect_array[0].infile.fd = -2;
			return ;
		}
		to_choice_here_doc(&cpy, i, *id_here_doc);
		*here_doc_available = 1;
		*id_here_doc = 1;
	}
}

static void	handle_redirects(int *i, t_minishell *shell)
{
	if (shell->cpy.tokens->type == TOKEN_REDIRECT_IN)
		handle_input_redirect(&shell->cpy, shell->cpy.tokens, i, shell);
	else if (shell->cpy.tokens->type == TOKEN_REDIRECT_OUT)
		handle_output_redirect(&shell->cpy, shell->cpy.tokens, i, shell);
	else if (shell->cpy.tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
		handle_output_redirect_append(&shell->cpy, shell->cpy.tokens, i, shell);
}

static void	handle_pipe_local(t_minishell cpy, int *i,
		t_minishell *shell, int *id_here_doc)
{
	if (cpy.tokens->type == TOKEN_PIPE)
	{
		if (cpy.tokens->next == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			shell->exit_status = 2;
			shell->redirect_array[0].infile.fd = -2;
			return ;
		}
		else
		{
			handle_pipe(&cpy, i);
			*id_here_doc = 0;
		}
	}
}

void	handle_input_output(t_minishell cpy, int *i,
		t_minishell *shell, int here_doc_available, int *id_here_doc)
{
	shell->cpy = cpy;
	handle_heredoc(i, shell, &here_doc_available, id_here_doc);
	handle_redirects(i, shell);
	handle_pipe_local(i, shell, id_here_doc);
}
