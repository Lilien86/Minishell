#include "../minishell.h"

void	handle_quotes(const char **input, t_token **head,
			t_minishell *shell, const char **start)
{

	(void)start;

	if (**input == '\'' || **input == '"')
	{
		add_quoted_token(input, head, **input, shell);
		// if (*input != *start)
		// {
		// 	word = ft_strndup(*start, (size_t)(*input - *start));
		// 	//add_token(head, init_token(TOKEN_WORD, word));
		// 	//free(word);
		// }

	}
	else
		(*input)++;
	// {
	// 	temp = append_char_to_str(final_value, **input);
	// 	if (temp)
	// 	{
	// 		final_value = temp;
	// 	}
	// 	(*input)++;
	// }

		
	//*start = *input;
	//return (temp);
}
