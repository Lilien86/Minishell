/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:30:00 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/30 13:51:06 by ybarbot          ###   ########.fr       */
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

void	add_token_based_on_char(const char **input,
	t_token **head, char **env, t_minishell *shell)
{
	identify_double_char_tokens(input, head, shell);
	if (**input == '>')
	{
		add_token(head, init_token(TOKEN_REDIRECT_OUT, ">", shell));
		(*input)++;
	}
	else if (**input == '<')
	{
		add_token(head, init_token(TOKEN_REDIRECT_IN, "<", shell));
		(*input)++;
	}
	else if (**input == '|')
	{
		add_token(head, init_token(TOKEN_PIPE, "|", shell));
		(*input)++;
	}
	else
		add_word_token(input, head, env, shell);
}

void	identify_and_add_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	if (is_special_char(**input))
		add_token_based_on_char(input, head, env, shell);
	else if (!ft_isspace(**input))
		add_word_token(input, head, env, shell);
}

t_token	*tokenize(const char *input, char **env, t_minishell *shell)
{
	t_token	*head;

	head = NULL;
	if (input)
	{
		while (*input)
		{
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '\0')
				break ;
			identify_and_add_token(&input, &head, env, shell);
		}
	}
	return (head);
}
