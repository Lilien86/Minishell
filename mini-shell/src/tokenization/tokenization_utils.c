#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*process_quoted_content(const char *quoted_part,
					char quote_type, t_minishell *shell)
{
	char	*value;

	if (quote_type == '"')
		value = substitute_env_vars(quoted_part, shell->env, shell);
	else
		value = ft_strdup(quoted_part);
	return (value);
}


void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, const char **start)
{
	char	*word;

	if (**input == '\'' || **input == '"')
	{
		if (*input != *start)
		{
			word = ft_strndup(*start, (size_t)(*input - *start));
			add_token(head, init_token(TOKEN_WORD, word));
			free(word);
		}
		add_quoted_token(input, head, **input, shell);
		*start = *input;
	}
	else
		(*input)++;
}
