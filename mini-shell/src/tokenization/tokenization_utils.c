#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}


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

void	identify_and_add_token(const char **input, t_token **head)
{
	if (**input == '\'' || **input == '"')
		add_quoted_token(input, head, **input);
	else if (is_special_char(**input))
		add_token_based_on_char(input, head);
	else if (!ft_isspace(**input))
		add_word_token(input, head);
}
