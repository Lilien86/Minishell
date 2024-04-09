#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static	char	*process_quoted_content(const char *quoted_part,
					char quote_type, char **env)
{
	char	*value;

	if (quote_type == '"')
		value = substitute_env_vars(quoted_part, env);
	else
		value = ft_strdup(quoted_part);
	return (value);
}

void	add_quoted_token(const char **input, t_token **head,
			char quote_type, char **env)
{
	const char	*start;
	size_t		len;
	char		*quoted_part;
	char		*value;

	(*input)++;
	start = *input;
	len = 0;
	while ((*input)[len] && (*input)[len] != quote_type)
		len++;
	if ((*input)[len] == quote_type)
	{
		quoted_part = ft_strndup(start, len);
		value = process_quoted_content(quoted_part, quote_type, env);
		add_token(head, init_token(TOKEN_WORD, value));
		free(quoted_part);
		free(value);
		*input += len + 1;
	}
	else
	{
		ft_printf("minishell: syntax error: missing quotes\n");
		free_tokens(head);
	}
}

void	add_word_token(const char **input, t_token **head, char **env)
{
	const char	*start;
	char		*word;
	size_t		len;
	char		*substituted_value;

	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		(*input)++;
	len = (size_t)(*input - start);
	if (len > 0)
	{
		word = ft_strndup(start, len);
		substituted_value = substitute_env_vars(word, env);
		add_token(head, init_token(TOKEN_WORD, substituted_value));
		free(word);
		free(substituted_value);
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
