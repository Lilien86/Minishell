/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:30:00 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 14:47:57 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	is_double_char;

	is_double_char = 0;
	if (identify_double_char_tokens(input, head, shell))
		is_double_char = 1;
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
	else if (!is_double_char)
		add_word_token(input, head, env, shell);
}

void	identify_and_add_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	if ((is_special_char(**input)) && (ft_strncmp(*input, "||", 2) != 0))
		add_token_based_on_char(input, head, env, shell);
	else if (!ft_isspace(**input))
		add_word_token(input, head, env, shell);
}

static int	check_first_argument(const char **input, t_minishell *shell)
{
	while (**input && ft_isspace(**input))
		(*input)++;
	if (**input == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		shell->exit_status = 2;
		shell->reset_exc = 1;
		return (1);
	}
	return (0);
}

t_token	*tokenize(const char *input, char **env, t_minishell *shell)
{
	t_token	*head;

	head = NULL;
	shell->syntax_error = 0;
	if (input)
	{
		if (check_first_argument(&input, shell) != 0)
			return (NULL);
		while (*input)
		{
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '\0')
				break ;
			identify_and_add_token(&input, &head, env, shell);
			if (shell->syntax_error == 1)
			{
				free_tokens(&head);
				return (NULL);
			}
		}
	}
	return (head);
}
