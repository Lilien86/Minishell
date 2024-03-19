/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:42:13 by lauger            #+#    #+#             */
/*   Updated: 2024/03/19 10:21:45 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_special_char(char c) {
    return (c == '>' || c == '<' || c == '|' || c == '~' || c == '\'' ||
            c == '"' || c == '$' || c == '?');
}

void add_special_token(const char **input, t_token **head, t_token_type type) {
    char value[3] = {0}; // Increased size to handle double-char tokens
    value[0] = **input;
    if ((**input == '>' && *(*input + 1) == '>') || 
        (**input == '<' && *(*input + 1) == '<') || 
        (**input == '$' && *(*input + 1) == '?')) {
        value[1] = *(*input + 1);
        (*input)++;
    }
    add_token(head, init_token(type, value));
}

void add_quoted_token(const char **input, t_token **head, char quoteType) {
    const char *start = *input + 1; // Skip the opening quote
    size_t len = 0;
    while (start[len] && start[len] != quoteType) {
        len++;
    }
    char *value = ft_strndup(start, len);
    add_token(head, init_token(quoteType == '"' ? TOKEN_DOUBLE_QUOTE : TOKEN_SINGLE_QUOTE, value));
    free(value);
    *input = start + len; // Move input pointer past the closing quote
}

void add_word_token(const char **input, t_token **head) {
    const char *start = *input;
    while (**input && !ft_isspace(**input) && !is_special_char(**input)) {
        (*input)++;
    }
    size_t len = (size_t)(*input - start);
    if (len > 0) {
        char *value = ft_strndup(start, len);
        add_token(head, init_token(TOKEN_WORD, value));
        free(value);
        (*input)--; // Move back one to correctly process next character
    }
}

void free_tokens(t_token **tokens) {
    while (*tokens) {
        t_token *tmp = (*tokens)->next;
        free((*tokens)->value);
        free(*tokens);
        *tokens = tmp;
    }
}
