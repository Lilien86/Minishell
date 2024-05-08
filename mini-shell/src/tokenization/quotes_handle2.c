#include "../minishell.h"

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, const char **start)
{
	//char	*word;
	char *final_value;

	if (**input == '\'' || **input == '"')
	{
		final_value = add_quoted_token(input, head, **input, shell);
		// if (*input != *start)
		// {
		// 	word = ft_strndup(*start, (size_t)(*input - *start));
		// 	//add_token(head, init_token(TOKEN_WORD, word));
		// 	//free(word);
		// }
		*start = *input;
	}
	else
		(*input)++;
}
