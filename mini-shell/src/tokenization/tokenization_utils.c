#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static	char	*process_quoted_content(const char *quoted_part,
					char quote_type, t_minishell *shell)
{
	char	*value;

	if (quote_type == '"')
		value = substitute_env_vars(quoted_part, shell->env, shell);
	else
		value = ft_strdup(quoted_part);
	return (value);
}

void	add_quoted_token(const char **input, t_token **head,
			char quote_type, t_minishell *shell)
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
		value = process_quoted_content(quoted_part, quote_type, shell);
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

void	add_word_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	const char	*start;
	char		*word;
	char		*substituted_value;

	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		if (**input == '\'' || **input == '"')
		{
			if (*input != start)
			{
				word = ft_strndup(start, (size_t)(*input - start));
				add_token(head, init_token(TOKEN_WORD, word));
				free(word);
			}
			add_quoted_token(input, head, **input, shell);
			start = *input;
		}
		else
			(*input)++;
	if (*input > start)
	{
		word = ft_strndup(start, (size_t)(*input - start));
		substituted_value = substitute_env_vars(word, env, shell);
		add_token(head, init_token(TOKEN_WORD, substituted_value));
		free(word);
		free(substituted_value);
	}
	if (ft_isspace(**input) && (*head)->next && *(*input + 1) != '\0')
	{
		while (ft_isspace(*(*input + 1)))
			(*input)++;
		add_token(head, init_token(TOKEN_SPACE, " "));
	}
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
