#include "../minishell.h"

static void	print_error_and_set_status(char *msg, int status,
		t_minishell *shell)
{
	ft_putstr_fd(msg, 2);
	shell->exit_status = status;
}

static void	handle_exit_with_args(t_token *tokens, t_minishell *shell)
{
	t_token	*current;
	char	*endptr;
	long	exit_code;

	current = tokens->next;
	exit_code = ft_atoi_endptr(current->value, &endptr);
	if (*endptr == '\0' && current->next)
	{
		print_error_and_set_status("minishell: exit: too many arguments\n",
			1, shell);
		return ;
	}
	else if (*endptr != '\0')
		print_error_and_set_status("minishell: exit: numeric argument "
			"required\n", 2, shell);
	else
	{
    	shell->exit_status = exit_code % 256;
    	if (shell->exit_status < 0)
        	shell->exit_status += 256;
	}
}

void	ft_exit(t_token *tokens, t_minishell *shell)
{
	t_token	*current;
	int		local_exit_status;

	local_exit_status = shell->exit_status;
	current = tokens->next;
	if (!current)
	{
		local_exit_status = shell->exit_status;
		free_minishell(shell);
		ft_printf("exit\n");
		exit(local_exit_status);
	}
	handle_exit_with_args(tokens, shell);
	local_exit_status = shell->exit_status;
	ft_printf("exit\n");
	free_minishell(shell);
	exit(local_exit_status);
}
