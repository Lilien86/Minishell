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
}
