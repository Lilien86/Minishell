#include "../minishell.h"

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, char **token_temp)
{
	char		*word;
	const char	*start;
	int			len;
	char		*temp;

	shell->is_single_quote = 0;
	shell->is_double_quote = 0;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
	{
		word = NULL;
		if (**input == '\'' || **input == '"')
		{
			word = add_quoted_token(input, head, **input, shell);
			if (!word)
				return ;
			temp = ft_strjoinfree(*token_temp, word);
			free(word);
			if (!temp)
				return ;
			*token_temp = temp;
		}
		else
		{
			len = 0;
			start = *input;
			while ((*input)[len] && !ft_isspace((*input)[len])
				&& !is_special_char((*input)[len]) && (*input)[len]
				!= '\'' && (*input)[len] != '"' )
				len++;
			word = ft_strndup(start, (size_t)len);
			if (!word)
				return ;
			temp = substitute_env_vars_handle_quotes(word, shell->env, shell);
			free(word);
			if (!temp)
				return ;
			word = temp;
			temp = ft_strjoinfree(*token_temp, word);
			free(word);
			if (!temp)
				return ;
			*token_temp = temp;
			(*input) += len;
		}
	}
}

void	append_segment(char **final_value, char *segment)
{
	char	*temp;

	if (!segment)
		return ;
	temp = ft_strjoinfree(*final_value, segment);
	if (!temp)
		return ;
	*final_value = temp;
}

int	handle_syntax_error(char **final_value,
				t_token **head, char quote_type)
{
	ft_printf("minishell: syntax error: missing closing quote '%c'\n",
		quote_type);
	free(*final_value);
	free_tokens(head);
	return (0);
}
