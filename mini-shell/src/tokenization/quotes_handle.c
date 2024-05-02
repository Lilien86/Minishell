/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:07:03 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/02 12:33:15 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void process_quoted_part(const char *start, size_t len, t_token **head, char quote_type, t_minishell *shell)
// {
//     static char *empty_str = "";
//     char *quoted_part;
//     char *value;

//     if (len == 0)
//     {
//         add_token(head, init_token(TOKEN_WORD, empty_str));
//         return;
//     }
//     quoted_part = ft_strndup(start, len);
//     value = process_quoted_content(quoted_part, quote_type, shell);
//     add_token(head, init_token(TOKEN_WORD, value));
//     free(quoted_part);
//     free(value);
// }

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
    char *final_value;
    char *segment;
    char *processed_segment;
    char *temp;

    final_value = ft_strdup("");  // Start with an empty string to concatenate onto
    if (!final_value)
        return;  // Handle memory allocation failure

    while (**input == quote_type) {
        (*input)++;  // Skip the opening quote
        start = *input;  // Start of the quoted text
        len = find_quote_end(*input, quote_type);  // Find the end of the quote

        if ((*input)[len] != quote_type) {
            ft_printf("minishell: syntax error: missing closing quote '%c'\n", quote_type);
            free(final_value);
            free_tokens(head);  // Free all tokens due to syntax error
            return;
        }

        segment = ft_strndup(start, len);
        if (!segment) {
            free(final_value);
            return;  // Handle memory allocation failure
        }
        processed_segment = process_quoted_content(segment, quote_type, shell);
        free(segment);
        if (!processed_segment) {
            free(final_value);
            return;  // Handle memory allocation failure
        }

        temp = ft_strjoin(final_value, processed_segment);
	
       	//free(final_value);
        free(processed_segment);
        if (!temp) {
            return;  // Handle memory allocation failure
        }
        final_value = temp;

        *input += len + 1;  // Move past the closing quote
    }

    if (final_value[0] != '\0')
        add_token(head, init_token(TOKEN_WORD, final_value));
    free(final_value);
}

