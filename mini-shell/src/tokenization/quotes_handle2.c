#include "../minishell.h"

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, char **token_temp)
{
	char	*word;

	while (**input && !ft_isspace(**input) && !is_special_char(**input))
	{
		word = NULL;
		if (**input == '\'' || **input == '"')
		{
			word = add_quoted_token(input, head, **input, shell);
			if (!word)
				return ;
			*token_temp = ft_strjoin(*token_temp, word);
			if (!*token_temp)
				return ;
			free(word);
		}
		else
		{
			*token_temp = append_char_to_str(*token_temp, **input);
			if (!*token_temp)
				return ;
			(*input)++;
		}
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
