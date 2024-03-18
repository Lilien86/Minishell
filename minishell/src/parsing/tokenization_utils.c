/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:42:13 by lauger            #+#    #+#             */
/*   Updated: 2024/03/18 11:15:15 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == ';' \
	|| c == '\'' || c == '"' || c == '$' || c == '?');
}

void	add_special_token(const char **input, t_token **head, t_token_type type)
{
	char	value[2];

	value[0] = **input;
	value[1] = '\0';
	add_token(head, init_token(type, value));
	(*input)++;
}

void	add_word_token(const char **input, t_token **head)
{
	char	*word;
	char	*temp;
	char	to_add[2];

	word = NULL;
	word = ft_strdup("");
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
	{
		to_add[0] = **input;
		to_add[1] = '\0';
		temp = word;
		word = ft_strjoin(word, to_add);
		//free(temp);
		(*input)++;
	}
	if (word != NULL)
	{
		add_token(head, init_token(TOKEN_WORD, word));
		free(word);
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
}
