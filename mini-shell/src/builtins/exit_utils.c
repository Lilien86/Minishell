/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:03 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/03 14:52:32 by ybarbot          ###   ########.fr       */
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
    int	i;
    const char *p;

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
