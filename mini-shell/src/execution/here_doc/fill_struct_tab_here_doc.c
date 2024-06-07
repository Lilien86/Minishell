/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_tab_here_doc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:44:31 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/07 16:28:42 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	counter_here_doc(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_HEREDOC)
			count++;
		if (tokens->type == TOKEN_PIPE)
			break ;
		tokens = tokens->next;
	}
	return (count);
}

static void	init_here_doc_tab(t_file **tab_here_doc, int i,
	t_token *current, t_minishell *shell)
{
	tab_here_doc[i] = ft_calloc(((size_t)counter_here_doc(current) + 1),
			sizeof(t_file));
	if (tab_here_doc[i] == NULL)
		error_exit("Error malloc here_doc", shell);
}

static void	process_here_doc_token(t_token *current, t_minishell *shell,
	t_file **tab_here_doc, t_coord *coord)
{
	if (current->next->quote_type != SINGLE_QUOTE)
		coord->replace_env = 1;
	if (coord->j == 0)
		init_here_doc_tab(tab_here_doc, coord->i, current, shell);
	tab_here_doc[coord->i][coord->j] = here_doc(
			current, shell, coord->replace_env, tab_here_doc);
	tab_here_doc[coord->i][coord->j].is_allocated = 1;
	(coord->j)++;
}

static int	isnt_token_word(t_token *current)
{
	if (current->next->type == TOKEN_PIPE
		|| current->next->type == TOKEN_REDIRECT_IN
		|| current->next->type == TOKEN_REDIRECT_OUT
		|| current->next->type == TOKEN_DOUBLE_REDIRECT_OUT
		|| current->next->type == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}

static void	process_token(t_token *current, t_minishell *shell,
		t_file **tab_here_doc, t_coord *coord)
{
	if (current->type == TOKEN_HEREDOC)
	{
		if (current->next == NULL || isnt_token_word(current) == 1)
		{
			ft_putstr_fd("minishell: syntax error"
				" near unexpected token `newline'\n", 2);
			shell->exit_status = 1;
			shell->redirect_array[0].infile.fd = -1;
			return ;
		}
		process_here_doc_token(current, shell, tab_here_doc,
			coord);
	}
	else if (current->type == TOKEN_PIPE)
	{
		coord->i++;
		coord->j = 0;
	}
}

t_file	**fill_tab_here_doc(t_token *current, t_minishell *shell,
	t_file **tab_here_doc, int replace_env)
{
	t_coord	coord;

	coord.i = 0;
	coord.j = 0;
	coord.replace_env = replace_env;
	while (current != NULL)
	{
		process_token(current, shell, tab_here_doc, &coord);
		current = current->next;
	}
	return (tab_here_doc);
}
