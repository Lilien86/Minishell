/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:48:37 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 13:14:04 by ybarbot          ###   ########.fr       */
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

static void	handle_input_output(t_minishell cpy, int *i, t_minishell *shell,
		int here_doc_available, int *id_here_doc)
{
	if (cpy.tokens->type == TOKEN_HEREDOC && here_doc_available == 0)
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
		here_doc_available = 1;
		*id_here_doc = 1;
	}
	if (cpy.tokens->type == TOKEN_REDIRECT_IN)
		handle_input_redirect(&cpy, cpy.tokens, i, shell);
	else if (cpy.tokens->type == TOKEN_REDIRECT_OUT)
		handle_output_redirect(&cpy, cpy.tokens, i, shell);
	else if (cpy.tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
		handle_output_redirect_append(&cpy, cpy.tokens, i, shell);
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

void	fill_redirect_array(t_minishell *shell)
{
	t_minishell	cpy;
	int			i;
	int			here_doc_available;
	static int	id_here_doc = 0;

	shell->tab_here_doc = run_here_doc(shell);
	cpy = *shell;
	here_doc_available = 0;
	i = 0;
	while (cpy.tokens != NULL)
	{
		handle_input_output(cpy, &i, shell, here_doc_available, &id_here_doc);
		if (cpy.tokens->type == TOKEN_WORD
			&& (cpy.tokens->value != cpy.redirect_array[i].infile.name
				&& cpy.tokens->value != cpy.redirect_array[i].outfile.name))
			handle_word(&cpy, &cpy.tokens, &i);
		else
		{
			if (cpy.tokens->type != TOKEN_PIPE && cpy.tokens->next != NULL)
				cpy.tokens = cpy.tokens->next;
			cpy.tokens = cpy.tokens->next;
		}
	}
	id_here_doc = 0;
}

void	fill_t_redirect(t_minishell *shell)
{
	if (!init_redirect_array(shell))
		return ;
	shell->redirect_array[0].infile.name = NULL;
	shell->redirect_array[0].infile.fd = -1;
	shell->redirect_array[0].infile.is_allocated = 0;
	shell->redirect_array[0].outfile.name = NULL;
	shell->redirect_array[0].outfile.fd = -1;
	shell->redirect_array[0].argv = NULL;
	fill_redirect_array(shell);
	//print_data(shell->redirect_array, shell->nb_cmds);
}
