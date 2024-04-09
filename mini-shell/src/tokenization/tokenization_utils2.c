#include "../minishell.h"

void	identify_and_add_token(const char **input, t_token **head, char **env)
{
	if (**input == '\'' || **input == '"')
		add_quoted_token(input, head, **input, env);
	else if (is_special_char(**input))
		add_token_based_on_char(input, head, env);
	else if (!ft_isspace(**input))
		add_word_token(input, head, env);
}
