#include "../minishell.h"

int	check_builtins(t_minishell *shell)
{
	if (!shell->tokens)
		return (0);
	if (ft_strncmp(shell->tokens->value, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(shell->tokens->value, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(shell->tokens->value, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->tokens->value, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(shell->tokens->value, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(shell->tokens->value, "env", 3) == 0
		&& shell->tokens->value[3] == '\0')
		return (1);
	else
		return (0);
}

int	is_token_redirection(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT
			|| tmp->type == TOKEN_DOUBLE_REDIRECT_OUT
				|| tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}