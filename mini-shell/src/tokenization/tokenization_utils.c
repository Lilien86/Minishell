/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:50 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:59:25 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_word_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	char		*token_temp;

	(void)env;
	shell->is_single_quote = 0;
	shell->is_double_quote = 0;
	token_temp = ft_strdup("");
	if (!token_temp)
		return ;
	if (**input && !ft_isspace(**input) && (!is_special_char(**input)
			|| ft_strncmp(*input, "||", 2) == 0))
	{
		handle_quotes(input, head, shell, &token_temp);
		if (shell->syntax_error == 1)
		{
			free(token_temp);
			return ;
		}
	}
	if ((*token_temp) || (token_temp[0] == '\0'
			&& (shell->is_double_quote || shell->is_single_quote)))
		add_token(head, init_token(TOKEN_WORD, token_temp, shell));
	free(token_temp);
}

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	update_input(const char **input)
{
	*input += 2;
	if (**input == '\0' || **input == ' ')
	{
		if (**input != '\0')
			*input += 1;
		while (**input == ' ')
			*input += 1;
	}
}

int	identify_double_char_tokens(const char **input, t_token **head,
		t_minishell *shell)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(head, init_token(TOKEN_DOUBLE_REDIRECT_OUT, ">>", shell));
		update_input(input);
		return (1);
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(head, init_token(TOKEN_HEREDOC, "<<", shell));
		update_input(input);
		return (1);
	}
	return (0);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	*tokens = NULL;
}
