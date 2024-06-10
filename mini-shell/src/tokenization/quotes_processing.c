/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:27:55 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/10 19:20:54 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_quotes(const char **input, t_token **head,
		t_minishell *shell, char **token_temp)
{
	char	*word;
	char	*temp;

	word = add_quoted_token(input, head, **input, shell);
	if (!word)
		return ;
	temp = ft_strjoinfree(*token_temp, word);
	free(word);
	if (!temp)
		return ;
	*token_temp = temp;
}

static char	*get_word(const char **input)
{
	const char	*start;
	int			len;
	char		*word;

	len = 0;
	start = *input;
	while ((*input)[len] && !ft_isspace((*input)[len])
		&& (!is_special_char((*input)[len])
		|| ft_strncmp(*input, "||", 2) == 0) && (*input)[len]
		!= '\'' && (*input)[len] != '"' && ((*input)[len] != '$'
		|| ((*input)[len + 1] != '\0' && ((*input)[len + 1]
		!= '\'' && (*input)[len + 1] != '"'))))
		len++;
	if ((*input)[len] == '$' && (*input)[len + 1] == '\0')
		len++;
	word = ft_strndup(start, (size_t)len);
	*input += len;
	return (word);
}

static void	process_non_quoted_segment(const char **input, t_minishell *shell,
				char **token_temp)
{
	char		*word;
	char		*temp;

	word = get_word(input);
	if (!word)
		return ;
	temp = substitute_env_vars_handle_quotes(word, shell->env, shell);
	free(word);
	if (!temp)
		return ;
	word = temp;
	temp = ft_strjoinfree(*token_temp, word);
	free(word);
	if (!temp)
		return ;
	*token_temp = temp;
}

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, char **token_temp)
{
	while (**input && !ft_isspace(**input)
		&& (!is_special_char(**input)
			|| ft_strncmp(*input, "||", 2) == 0) && shell->syntax_error == 0)
	{
		shell->is_single_quote = 0;
		shell->is_double_quote = 0;
		if (**input == '\'' || **input == '"')
			process_quotes(input, head, shell, token_temp);
		else if (**input == '$' && *(*input + 1) != '\0'
			&& (*(*input + 1) == '\'' || *(*input + 1) == '"'))
		{
			(*input)++;
			process_quotes(input, head, shell, token_temp);
		}
		else
		{
			process_non_quoted_segment(input, shell, token_temp);
			if (shell->syntax_error == 1)
				return ;
		}
	}
}

void	append_segment(char **final_value, char *segment)
{
	char	*temp;

	if (!segment)
		return ;
	temp = ft_strjoinfree(*final_value, segment);
	if (!temp)
		return ;
	*final_value = temp;
}
