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
			if (word)
			{
				ft_strjoin(*token_temp, word);
				//free(word);
			}
		}
		else
		{
			word = append_char_to_str(*token_temp, **input);
			if (word)
			{
				ft_strjoin(*token_temp, word);
				//free(word);
			}
			(*input)++;
		}
	}

}
