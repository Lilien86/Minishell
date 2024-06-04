/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:12 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:31:09 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_and_set_status(char *msg, int status,
		t_minishell *shell)
{
	ft_putstr_fd(msg, 2);
	shell->exit_status = status;
}

static	int	check_length_and_value(t_token *current, t_minishell *shell)
{
	if (ft_strlen(current->value) == 19
		&& (current->value[0] != '-' || current->value[0] != '+'))
	{
		if (ft_strncmp(current->value, "9223372036854775807", 19) > 0)
		{
			print_error_and_set_status("minishell: exit: numeric argument "
				"required\n", 2, shell);
			return (0);
		}
	}
	if (ft_strlen(current->value) == 20
		&& (current->value[0] == '-' || current->value[0] == '+'))
	{
		if (ft_strncmp(current->value, "-9223372036854775808", 20) > 0)
		{
			print_error_and_set_status("minishell: exit: numeric argument "
				"required\n", 2, shell);
			return (0);
		}
	}
	return (1);
}

int	check_exit_arg_validity(t_token *current,
				t_minishell *shell, int *i)
{
	int	i_sign;

	i_sign = *i - 1;
	while (current->value[*i])
	{
		if (!ft_isdigit(current->value[*i]))
		{
			print_error_and_set_status("minishell: exit: numeric argument "
				"required\n", 2, shell);
			return (0);
		}
		(*i)++;
	}
	if (!check_length_and_sign(current, shell, i_sign))
		return (0);
	if (check_length_and_value(current, shell) == 0)
		return (0);
	else
		return (1);
}

static void	handle_exit_with_args(t_token *tokens, t_minishell *shell)
{
	t_token		*current;
	char		*endptr;
	long long	exit_code;
	int			i;

	i = 0;
	current = tokens->next;
	if (!process_exit_arg(current, shell, &i))
		return ;
	exit_code = ft_atoi_endptr(current->value, &endptr);
	if (check_numbers_arg_exit(endptr, current, shell) == 0)
		return ;
	if (*endptr != '\0')
		print_error_and_set_status("minishell: exit: numeric"
			" argument required\n", 2, shell);
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
		free_tokens(&tokens);
		exit(local_exit_status);
	}
	handle_exit_with_args(tokens, shell);
	local_exit_status = shell->exit_status;
	ft_printf("exit\n");
	free_tokens(&tokens);
	free_minishell(shell);
	exit(local_exit_status);
}
