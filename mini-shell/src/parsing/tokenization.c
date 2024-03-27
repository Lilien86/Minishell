#include "../minishell.h"

/**
 * @brief Initializes a token with the given type and value.
 *
 * This function allocates memory for a new token, sets its type and value,
 * and initializes the next pointer to NULL.
 *
 * @param type The type of the token.
 * @param value The value of the token.
 * @return A pointer to the newly initialized token, or NULL if memory allocation fails.
 */
t_token *init_token(t_token_type type, char *value)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

/**
 * @brief Adds a token to the end of the token list.
 *
 * @param head The head of the token list.
 * @param new_token The token to be added.
 */
void add_token(t_token **head, t_token *new_token)
{
	t_token *temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

/**
 * @brief Identifies and adds double character tokens to the token list.
 *
 * @param input The input string.
 * @param head The head of the token list.
 */
void identify_double_char_tokens(const char **input, t_token **head)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(head, init_token(TOKEN_DOUBLE_REDIRECT_OUT, ">>"));
		*input += 2;
		return;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(head, init_token(TOKEN_HEREDOC, "<<"));
		*input += 2;
		return;
	}
}

/**
 * @brief Adds a token based on the current character in the input string.
 *
 * @param input The input string.
 * @param head The head of the token list.
 */
void add_token_based_on_char(const char **input, t_token **head)
{
	identify_double_char_tokens(input, head);
	if (**input == '>')
		add_token(head, init_token(TOKEN_REDIRECT_OUT, ">"));
	else if (**input == '<')
		add_token(head, init_token(TOKEN_REDIRECT_IN, "<"));
	else if (**input == '|')
		add_token(head, init_token(TOKEN_PIPE, "|"));
	else
		add_word_token(input, head);
}

/**
 * @brief Tokenizes the input string and creates a linked list of tokens.
 *
 * takes a null-terminated string as input and tokenizes it based on whitespace characters.
 * It creates a linked list of tokens, where each token represents a substring of the input string.
 *
 * @param input The input string to be tokenized.
 * @return A pointer to the head of the token linked list.
 */
t_token	*tokenize(const char *input)
{
	t_token	*head;

	head = NULL;
	if (input)
		while (*input) 
		{
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '\0')
				break ;
			identify_and_add_token(&input, &head);
			if (*input)
				input++;
		}
	return (head);
}
