#include "../minishell.h"

/**
 * @brief Checks if a character is a special character.
 * 
 * @param c The character to be checked.
 * @return 1 if the character is a special character, 0 otherwise.
 */
int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

/**
 * @brief Adds a quoted token to the token list.
 *
 * This function takes an input string, a token list head, and a quote type as parameters.
 * It searches for the closing quote character in the input string and extracts the quoted value.
 * If the closing quote is found, it creates a new token with the extracted value and adds it to the token list.
 * If the closing quote is not found, it prints an error message and frees the token list.
 *
 * @param input The input string containing the quoted token.
 * @param head The head of the token list.
 * @param quote_type The type of quote character used for the token.
 */
void	add_quoted_token(const char **input, t_token **head, char quote_type)
{
	char		*value;
	const char	*start;
	size_t		len;

	start = *input;
	(*input)++;
	len = 0;
	while ((*input)[len] && (*input)[len] != quote_type)
		len++;
	if ((*input)[len] == quote_type)
	{
		value = ft_strndup(start, len + 2);
		add_token(head, init_token(TOKEN_WORD, value));
		free(value);
		*input += len;
	}
	else
	{
		ft_printf("minishell: syntax error: missing quotes\n");
		free_tokens(head);
	}
}

/**
 * @brief Adds a word token to the token list.
 *
 * This function scans the input string and extracts a word token, which is a sequence of characters
 * that is not whitespace or a special character. It then creates a token with the extracted value
 * and adds it to the token list.
 *
 * @param input The input string to scan for word tokens.
 * @param head A pointer to the head of the token list.
 */
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
    }
    if (**input)
		(*input)--;
}

/**
 * @brief Frees the memory allocated for a linked list of tokens.
 * 
 * This function iterates through the linked list of tokens and frees the memory
 * allocated for each token. It also sets the pointer to the linked list to NULL
 * after freeing all the tokens.
 * 
 * @param tokens A pointer to the linked list of tokens.
 */
void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

/**
 * @brief Identifies and adds a token based on the input character.
 *
 * This function takes a pointer to the input string and a pointer
 * to the head of the token list.
 * It identifies the type of token based on
 * the input character and adds it to the token list.
 *
 * @param input Pointer to the input string.
 * @param head Pointer to the head of the token list.
 */
void	identify_and_add_token(const char **input, t_token **head)
{
	if (**input == '\'' || **input == '"')
		add_quoted_token(input, head, **input);
	else if (is_special_char(**input))
		add_token_based_on_char(input, head);
	else if (!ft_isspace(**input))
		add_word_token(input, head);
}
