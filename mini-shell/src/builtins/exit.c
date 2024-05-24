#include "../minishell.h"

static void	print_error_and_set_status(char *msg, int status,
		t_minishell *shell)
{
	ft_putstr_fd(msg, 2);
	shell->exit_status = status;
}

static void	handle_exit_with_args(t_token *tokens, t_minishell *shell)
{
	t_token		*current;
	char		*endptr;
	long long	exit_code;
	int			i;

	i= 0;
	current = tokens->next;
	if (current->value[0] == '-' || current->value[0] == '+')
		i++;
	while (current->value[i])
	{
		if (!ft_isdigit(current->value[i]))
		{
			print_error_and_set_status("minishell: exit: numeric argument "
				"required\n", 2, shell);
			return ;
		}
		i++;
	}
	if ((ft_strlen(current->value) > 19 && current->value[0]
			!= '-' && current->value[0] != '+'))
	{
		print_error_and_set_status("minishell: exit: numeric argument "
			"required\n", 2, shell);
		return ;
	}
	if ((ft_strlen(current->value) > 20
			&& (current->value[0] == '-' || current->value[0] == '+')))
	{
		print_error_and_set_status("minishell: exit: numeric argument "
			"required\n", 2, shell);
		return ;
	}
	if (ft_strlen(current->value) == 19
		&& (current->value[0] != '-' || current->value[0] != '+'))
	{
		if (ft_strncmp(current->value, "9223372036854775807", 19) > 0)
		{
			print_error_and_set_status("minishell: exit: numeric argument "
				"required\n", 2, shell);
			return ;
		}
	}
	if (ft_strlen(current->value) == 20
		&& (current->value[0] == '-' || current->value[0] == '+'))
	{
		if (ft_strncmp(current->value, "-9223372036854775808", 20) > 0)
		{
			print_error_and_set_status("minishell: exit: numeric argument "
				"required\n", 2, shell);
			return ;
		}
	}
	exit_code = ft_atoi_endptr(current->value, &endptr);
	if (*endptr == '\0' && current->next)
	{
		print_error_and_set_status("minishell: exit: too many arguments\n",
			1, shell);
		return ;
	}
	if (*endptr != '\0')
		print_error_and_set_status("minishell: exit: numeric argument "
			"required\n", 2, shell);
	else
	{
		exit_code %= 256;
		if (exit_code < 0)
			exit_code += 256;
		shell->exit_status = (int) exit_code;
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
	free_tokens(&tokens);
	free_minishell(shell);
	exit(local_exit_status);
}
