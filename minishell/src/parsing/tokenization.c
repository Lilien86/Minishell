/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:40:54 by lauger            #+#    #+#             */
/*   Updated: 2024/03/19 11:07:45 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//Initializes a new token with the given type and value.
//Returns a pointer to the newly created token.
t_token	*init_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

void identify_double_char_tokens(const char **input, t_token **head)
{
	if (**input == '$' && *(*input + 1) == '?')
	{
		add_token(head, init_token(TOKEN_EXIT_STATUS, "$?"));
		*input += 2;
		return;
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(head, init_token(TOKEN_DOUBLE_REDIRECT_OUT, ">>"));
		*input += 2;
		return;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(head, init_token(TOKEN_HEREDOC, "<<"));
		*input += 2;
		return;
	}
}

void identify_and_add_token(const char **input, t_token **head)
{
	if (**input == '\'' || **input == '"')
		add_quoted_token(input, head, **input);
	else if (is_special_char(**input))
	{
		t_token_type type = TOKEN_WORD;
		add_special_token(input, head, type);
	}
	else if (!ft_isspace(**input))
		add_word_token(input, head);
}

t_token	*tokenize(const char *input)
{
	t_token	*head;

	head = NULL;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		identify_and_add_token(&input, &head);
		if (*input)
			input++;
	}
	return (head);
}
