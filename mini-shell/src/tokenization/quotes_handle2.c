#include "../minishell.h"

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, char **token_temp)
{
	char	*word;

	while (**input && !ft_isspace(**input) && !is_special_char(**input))
	{
		if (**input == '\'' || **input == '"')
		{
			*token_temp = add_quoted_token(input, head, **input, shell);
		}
		else
		{
			word = append_char_to_str(*token_temp, **input);
			if (word)
			{
				*token_temp = word;
			}
			(*input)++;
		}
	}

}
