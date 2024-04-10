#include "../minishell.h"

void	identify_and_add_token(const char **input, t_token **head, char **env, t_minishell *shell)
{
	if (**input == '\'' || **input == '"')
		add_quoted_token(input, head, **input, shell);
	else if (is_special_char(**input))
		add_token_based_on_char(input, head, env, shell);
	else if (!ft_isspace(**input))
		add_word_token(input, head, env, shell);
}
