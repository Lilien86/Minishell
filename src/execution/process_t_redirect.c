/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_t_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:58:15 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/13 14:08:42 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_index_and_available_here_doc	*initialize_variables(t_minishell *shell,
		t_minishell *cpy, int *id_here_doc)
{
	t_index_and_available_here_doc	*index_and_available_here;

	shell->tab_here_doc = run_here_doc(shell);
	*cpy = *shell;
	index_and_available_here = ft_calloc(
			1, sizeof(t_index_and_available_here_doc));
	if (!index_and_available_here)
		error_exit("Error malloc index_and_available_here", shell);
	index_and_available_here->here_doc_available = 0;
	index_and_available_here->i = 0;
	*id_here_doc = 0;
	return (index_and_available_here);
}

static void	process_tokens(t_minishell *cpy,
	t_index_and_available_here_doc *index_and_available_here,
	t_minishell *shell, int *id_here_doc)
{
	while (cpy->tokens != NULL)
	{
		handle_input_output(*cpy, index_and_available_here, shell, id_here_doc);
		if (cpy->tokens->type == TOKEN_WORD
			&& (cpy->tokens->value != cpy->redirect_array
				[index_and_available_here->i].infile.name
				&& cpy->tokens->value != cpy->redirect_array
				[index_and_available_here->i].outfile.name))
			handle_word(cpy, &cpy->tokens, &index_and_available_here->i);
		else
		{
			if (cpy->tokens->type != TOKEN_PIPE && cpy->tokens->next != NULL)
				cpy->tokens = cpy->tokens->next;
			cpy->tokens = cpy->tokens->next;
		}
	}
}

void	fill_redirect_array(t_minishell *shell)
{
	t_minishell							cpy;
	t_index_and_available_here_doc		*index_and_available_here;
	static int							id_here_doc;

	index_and_available_here = initialize_variables(shell, &cpy, &id_here_doc);
	process_tokens(&cpy, index_and_available_here, shell, &id_here_doc);
	free(index_and_available_here);
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
	if (shell->reset_exc == 0)
		shell->exit_status = 0;
	fill_redirect_array(shell);
	shell->reset_exc = 0;
}
