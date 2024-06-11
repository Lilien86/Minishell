/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:39:47 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:58:27 by ybarbot          ###   ########.fr       */
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

char	*append_char_to_str(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = ft_calloc(sizeof(char), (len + 2));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
