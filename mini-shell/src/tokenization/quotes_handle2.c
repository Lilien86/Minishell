#include "../minishell.h"

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, char **token_temp)
{
	char	*word;
	const char	*start;
	int 		len;

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
			*token_temp = ft_strjoinfree(*token_temp, word);
			if (!*token_temp)
				return ;
			free(word);
		}
		else
		{
			len = 0;
			start = *input;
			while ((*input)[len] && !ft_isspace((*input)[len]) && !is_special_char((*input)[len]) && (*input)[len] != '\'' && (*input)[len] != '"' )
				len++;
			word = ft_strndup(start, (size_t)len);
			if (!word)
				return ;
			word = substitute_env_vars(word, shell->env, shell);
			append_segment(token_temp, word);
			if (!*token_temp)
				return ;
			(*input)+= len;
			free(word);
		}
	}
}
