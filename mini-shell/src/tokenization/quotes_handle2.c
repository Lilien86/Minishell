#include "../minishell.h"

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

char	*process_single_quote(const char **input, char *result,
			t_minishell *shell)
{
	char	*temp;
	int		start;
	//char	*to_free;

	(void)shell;
	start = (int)(*input - result);
	(*input)++;
	while (**input && **input != '\'')
		(*input)++;
	temp = ft_substr(result, (unsigned int)start,
			(size_t)((*input) - result - start));
	//to_free = result;
	result = ft_strjoin(result, temp);
	free(temp);
	return (result);
}
