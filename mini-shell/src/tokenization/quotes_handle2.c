/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:27:55 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/31 11:59:13 by ybarbot          ###   ########.fr       */
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

static void	process_non_quoted_segment(const char **input, t_minishell *shell,
				char **token_temp)
{
	const char	*start;
	int			len;
	char		*word;
	char		*temp;

	len = 0;
	start = *input;
	while ((*input)[len] && !ft_isspace((*input)[len])
		&& !is_special_char((*input)[len]) && (*input)[len]
			!= '\'' && (*input)[len] != '"')
			len++;
	word = ft_strndup(start, (size_t)len);
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
	*input += len;
}

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, char **token_temp)
{
	while (**input && !ft_isspace(**input) && !is_special_char(**input) && shell->syntax_error == 0)
	{
		shell->is_single_quote = 0;
		shell->is_double_quote = 0;
		if (**input == '\'' || **input == '"')
			process_quotes(input, head, shell, token_temp);
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

int	handle_syntax_error(char **final_value,
				t_token **head, char quote_type)
{
	(void)quote_type;
	ft_putstr_fd("minishell: syntax error: missing closing quote\n", 2);
	free(*final_value);
	free_tokens(head);
	return (0);
}
