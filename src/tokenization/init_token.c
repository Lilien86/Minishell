/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:22:48 by lauger            #+#    #+#             */
/*   Updated: 2024/06/10 18:23:17 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(t_token_type type, char *value, t_minishell *shell)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->type = type;
	if (shell->is_single_quote == 1)
		token->quote_type = SINGLE_QUOTE;
	else if (shell->is_double_quote == 1)
		token->quote_type = DOUBLE_QUOTE;
	else
		token->quote_type = NO_QUOTE;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}
