/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:52:01 by ybarbot           #+#    #+#             */
/*   Updated: 2024/03/19 11:00:18 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '~' || c == '\'' ||
			c == '"' || c == '$' || c == '?');
}

void	add_special_token(const char **input, t_token **head, t_token_type type)
{
	char	value[3] = {0};

	value[0] = **input;
	if ((**input == '>' && *(*input + 1) == '>') || 
		(**input == '<' && *(*input + 1) == '<') || 
		(**input == '$' && *(*input + 1) == '?'))
	{
		value[1] = *(*input + 1);
		(*input)++;
	}
	add_token(head, init_token(type, value));
}

void	add_quoted_token(const char **input, t_token **head, char quote_type)
{
	const char	*start = *input + 1;
	size_t		len = 0;
	char		*value;

	while (start[len] && start[len] != quote_type)
		len++;
	value = ft_strndup(start, len);
	add_token(head, init_token(quote_type == '"' ? TOKEN_DOUBLE_QUOTE : TOKEN_SINGLE_QUOTE, value));
	free(value);
	*input = start + len;
}

void	add_word_token(const char **input, t_token **head)
{
	const char	*start;
	size_t		len;

	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		(*input)++;
	len = (size_t)(*input - start);
	if (len > 0)
	{
		char *value = ft_strndup(start, len);
		add_token(head, init_token(TOKEN_WORD, value));
		free(value);
		(*input)--;
	}
}

void free_tokens(t_token **tokens)
{
    t_token *current;
    t_token *next;

    current = *tokens; // Début de la liste
    while (current != NULL) {
        next = current->next; // Sauvegarde du pointeur vers le prochain nœud
        free(current->value); // Libération de la chaîne de caractères
        free(current); // Libération du nœud actuel
        current = next; // Passage au nœud suivant
    }
    *tokens = NULL; // Sécurité pour éviter un pointeur vers une zone libérée
}

