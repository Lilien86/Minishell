/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:27:27 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/29 12:11:00 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	size_t	find_quote_end(const char *input, char quote_type)
{
	size_t	len;

	len = 0;
	while (input[len] && input[len] != quote_type)
		len++;
	return (len);
}

char	*process_quoted_content(const char *quoted_part,
		char quote_type, t_minishell *shell)
{
	char	*value;

	if (quote_type == '"' || quote_type != '\'')
		value = substitute_env_vars(quoted_part, shell->env, shell);
	else
	{
		value = ft_strdup(quoted_part);
		if (!value)
			return (NULL);
	}
	return (value);
}

static	char	*process_quoted_segment(const char *start,
		size_t len, char quote_type, t_minishell *shell)
{
	char	*segment;
	char	*processed_segment;

	segment = ft_strndup(start, len);
	if (!segment)
		return (NULL);
	processed_segment = process_quoted_content(segment, quote_type, shell);
	free(segment);
	return (processed_segment);
}

static int	process_segment(const char **input, char quote_type,
			char **final_value, t_minishell *shell)
{
	const char	*start;
	size_t		len;
	char		*segment;

	start = *input;
	len = find_quote_end(*input, quote_type);
	if ((*input)[len] != quote_type)
		return (handle_syntax_error(final_value, &(shell->tokens), quote_type));
	if (quote_type == '\'')
		shell->is_single_quote = 1;
	else if (quote_type == '"')
		shell->is_double_quote = 1;
	segment = process_quoted_segment(start, len, quote_type, shell);
	if (!segment)
	{
		free(*final_value);
		free_tokens(&(shell->tokens));
		return (0);
	}
	append_segment(final_value, segment);
	free(segment);
	*input += len + 1;
	return (1);
}

char	*add_quoted_token(const char **input, t_token **head,
			char quote_type, t_minishell *shell)
{
	char	*final_value;

	(void)head;
	final_value = ft_strdup("");
	if (!final_value)
		return (NULL);
	while (**input == quote_type)
	{
		(*input)++;
		if (!process_segment(input, quote_type, &final_value, shell))
			return (NULL);
	}
	return (final_value);
}
