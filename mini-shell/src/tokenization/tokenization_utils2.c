#include "../minishell.h"

void	identify_and_add_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	if (is_special_char(**input))
		add_token_based_on_char(input, head, env, shell);
	else if (!ft_isspace(**input))
		add_word_token(input, head, env, shell);
}

void	add_word_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	const char	*start;
	char		*word;
	char		*substituted_value;

	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		handle_quotes(input, head, shell, &start);
	if (*input > start)
	{
		word = ft_strndup(start, (size_t)(*input - start));
		substituted_value = substitute_env_vars(word, env, shell);
		add_token(head, init_token(TOKEN_WORD, substituted_value));
		free(word);
		free(substituted_value);
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}
