/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:58:15 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 13:58:26 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
