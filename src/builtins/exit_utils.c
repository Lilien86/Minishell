/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:03 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/12 11:26:11 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_numbers_arg_exit(char *endptr, t_token *current,
			t_minishell *shell)
{
	if (*endptr == '\0' && current->next)
	{
		print_error_and_set_status("minishell: exit: too many arguments\n",
			1, shell);
		return (0);
	}
	return (1);
}

int	strlen_without_space(const char *s)
{
	int			i;
	const char	*p;

	if (!s)
		return (0);
	p = s;
	while (ft_isspace(*p) && *p != '\0')
		p++;
	i = 0;
	while (p[i] != '\0')
		i++;
	return (i);
}

int	check_length_and_sign(t_token *current, t_minishell *shell,
				int i_sign)
{
	if ((strlen_without_space(current->value) > 19
			&& current->value[i_sign] != '-'
			&& current->value[i_sign] != '+')
		|| (strlen_without_space(current->value) > 20
			&& (current->value[i_sign] == '-'
				|| current->value[i_sign] == '+')))
	{
		print_error_and_set_status("minishell: exit: numeric "
			"argument required\n", 2, shell);
		return (0);
	}
	return (1);
}

int	process_exit_arg(t_token *current, t_minishell *shell, int *i)
{
	while (ft_isspace(current->value[*i]) && current->value[*i] != '\0')
		(*i)++;
	if (current->value[*i] == '-' || current->value[*i] == '+')
		(*i)++;
	if (check_exit_arg_validity(current, shell, i) == 0)
		return (0);
	return (1);
}
