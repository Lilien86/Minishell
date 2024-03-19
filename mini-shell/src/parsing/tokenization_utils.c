/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:52:01 by ybarbot           #+#    #+#             */
/*   Updated: 2024/03/19 12:38:04 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '~' || c == '\''
		|| c == '"' || c == '$' || c == '?');
}

void	add_special_token(const char **input, t_token **head, t_token_type type)
{
	char	value[3];

	ft_memset(value, 0, sizeof(value));
	value[0] = **input;
	if ((**input == '>' && *(*input + 1) == '>')
		|| (**input == '<' && *(*input + 1) == '<')
		|| (**input == '$' && *(*input + 1) == '?'))
	{
		value[1] = *(*input + 1);
		(*input)++;
	}
	add_token(head, init_token(type, value));
}

void	add_quoted_token(const char **input, t_token **head, char quote_type)
{
	const char	*start;
	size_t		len;
	char		*value;

	len = 0;
	start = *input + 1;
	while (start[len] && start[len] != quote_type)
		len++;
	if (quote_type == '"')
	{
		value = ft_strndup(start, len);
		add_token(head, init_token(TOKEN_DOUBLE_QUOTE, value));
	}
	else
	{
		value = ft_strndup(start, len);
		add_token(head, init_token(TOKEN_SINGLE_QUOTE, value));
	}
	free(value);
	*input = start + len;
}

void	add_word_token(const char **input, t_token **head)
{
	const char	*start;
	size_t		len;
	char		*value;

	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		(*input)++;
	len = (size_t)(*input - start);
	if (len > 0)
	{
		value = ft_strndup(start, len);
		add_token(head, init_token(TOKEN_WORD, value));
		free(value);
		(*input)--;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}
