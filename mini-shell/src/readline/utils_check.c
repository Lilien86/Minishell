#include "../minishell.h"

int	check_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0
		&& cmd[3] == '\0')
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