/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:40:54 by lauger            #+#    #+#             */
/*   Updated: 2024/03/15 08:41:02 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	identify_double_char_tokens(const char **input, t_token **head)
{
	if (**input == '$' && *(*input + 1) == '?')
	{
		add_token(head, init_token(TOKEN_EXIT_STATUS, "$?"));
		*input += 2;
		return ;
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(head, init_token(TOKEN_DOUBLE_REDIRECT_OUT, ">>"));
		*input += 2;
		return ;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(head, init_token(TOKEN_HEREDOC, "<<"));
		*input += 2;
		return ;
	}
}

void	identify_and_add_token(const char **input, t_token **head)
{
	t_token_type	type;

	type = TOKEN_WORD;
	identify_double_char_tokens(input, head);
	if (**input == '\0')
		return ;
	if (is_special_char(**input))
	{
		if (**input == '>')
			type = TOKEN_REDIRECT_OUT;
		else if (**input == '<')
			type = TOKEN_REDIRECT_IN;
		else if (**input == '|')
			type = TOKEN_PIPE;
		else if (**input == ';')
			type = TOKEN_SEMICOLON;
		else if (**input == '\'')
			type = TOKEN_SINGLE_QUOTE;
		else if (**input == '"')
			type = TOKEN_DOUBLE_QUOTE;
		else if (**input == '$')
			type = TOKEN_ENV_VAR;
		else if (**input == '?')
			type = TOKEN_EXIT_STATUS;
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

