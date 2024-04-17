#include "../minishell.h"

void	ft_exit(t_token *tokens, t_minishell *shell)
{
	t_token	*current;
	long	exit_code;
	char	*endptr;

	current = tokens->next;
	if (!current)
	{
		free_minishell(shell);
		ft_printf("exit\n");
		exit(shell->exit_status);
	}
	if (current && current->next)
	{
		strtol(current->value, &endptr, 10);
		if (*endptr == '\0')
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->exit_status = 1;
			return ;
		}
	}
	exit_code = strtol(current->value, &endptr, 10);
	if (*endptr != '\0')
	{
		ft_putstr_fd("minishell: exit: %s: numeric argument required\n", 2);
		shell->exit_status = 2;
	}
	else
		shell->exit_status = (int)exit_code;
	ft_printf("exit\n");
	free_minishell(shell);
	exit(shell->exit_status);
}
