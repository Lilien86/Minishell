/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:07:03 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/02 12:13:58 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void process_quoted_part(const char *start, size_t len, t_token **head, char quote_type, t_minishell *shell)
{
    static char *empty_str = "";
    char *quoted_part;
    char *value;

    if (len == 0)
    {
        add_token(head, init_token(TOKEN_WORD, empty_str));
        return;
    }
    quoted_part = ft_strndup(start, len);
    value = process_quoted_content(quoted_part, quote_type, shell);
    add_token(head, init_token(TOKEN_WORD, value));
    free(quoted_part);
    free(value);
}

static size_t find_quote_end(const char *input, char quote_type)
{
    size_t len = 0;
    while (input[len] && input[len] != quote_type)
    {
        len++;
    }
    return len;
}

void add_quoted_token(const char **input, t_token **head, char quote_type, t_minishell *shell)
{
    const char *start;
    size_t len;

    (*input)++;
    start = *input;
    len = find_quote_end(*input, quote_type);
    process_quoted_part(start, len, head, quote_type, shell);
    
    if ((*input)[len] == quote_type)
    {
        *input += len + 1;
    }
    else
    {
        ft_printf("minishell: syntax error: missing closing quote '%c'\n", quote_type);
        free_tokens(head);
    }
}
