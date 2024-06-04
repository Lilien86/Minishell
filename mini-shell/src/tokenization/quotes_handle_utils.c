/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:39:47 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:39:57 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_syntax_error(char **final_value,
				t_token **head, char quote_type)
{
	(void)quote_type;
	ft_putstr_fd("minishell: syntax error: missing closing quote\n", 2);
	free(*final_value);
	free_tokens(head);
	return (0);
}
