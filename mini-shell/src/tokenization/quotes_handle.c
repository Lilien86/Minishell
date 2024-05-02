/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:07:03 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/02 12:52:06 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t find_quote_end(const char *input, char quote_type)
{
    size_t len = 0;
    while (input[len] && input[len] != quote_type)
        len++;
    return len;
}

static char *process_quoted_segment(const char *start, size_t len, char quote_type, t_minishell *shell)
{
    char *segment;
    char *processed_segment;

    segment = ft_strndup(start, len);
    if (!segment)
        return NULL;
    processed_segment = process_quoted_content(segment, quote_type, shell);
    free(segment);
    return processed_segment;
}

static void append_segment(char **final_value, char *segment)
{
    char *temp;
	if (!segment)
		return;
    temp = ft_strjoin(*final_value, segment);
	if (temp)
	{
    	//free(*final_value);
    	*final_value = temp;
	}
}

void add_quoted_token(const char **input, t_token **head, char quote_type, t_minishell *shell)
{
    const char *start;
    size_t len;
    char *final_value;
    char *segment;

    final_value = ft_strdup("");
    while (**input == quote_type) {
        (*input)++;
        start = *input;
        len = find_quote_end(*input, quote_type);
        if ((*input)[len] != quote_type) {
            ft_printf("minishell: syntax error: missing closing quote '%c'\n", quote_type);
            free(final_value);
            free_tokens(head);
            return;
        }
        segment = process_quoted_segment(start, len, quote_type, shell);
        if (!segment) {
            free(final_value);
            return;
        }
        append_segment(&final_value, segment);
        free(segment);
        *input += len + 1;
    }
    if (final_value[0] != '\0')
        add_token(head, init_token(TOKEN_WORD, final_value));
    free(final_value);
}
