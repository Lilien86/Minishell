#include "../minishell.h"

void	add_word_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	const char	*start;
	char		*word;
	char		*substituted_value;

	(void)env;
	start = *input;
	while (**input && !ft_isspace(**input) && !is_special_char(**input))
		handle_quotes(input, head, shell, &start);
	
	if (*input > start)
	{
		word = ft_strndup(start, (size_t)(*input - start));
		substituted_value = substitute_env_vars(word, env, shell);
		add_token(head, init_token(TOKEN_WORD, substituted_value));
		free(substituted_value);
	}
	start = *input;
}

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	identify_double_char_tokens(const char **input, t_token **head)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(head, init_token(TOKEN_DOUBLE_REDIRECT_OUT, ">>"));
		*input += 2;
		return ;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(head, init_token(TOKEN_HEREDOC, "<<"));
		*input += 2;
		return ;
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
