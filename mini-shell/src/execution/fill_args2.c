/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:07:27 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 13:08:17 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *message, t_minishell *shell)
{
	ft_putstr_fd(message, 2);
	shell->exit_status = 1;
	free_minishell(shell);
	exit(EXIT_FAILURE);
}
