/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:31:35 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/28 10:31:39 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	length_until_plus_equal(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '+')
		len++;
	return (len);
}

void	remove_plus_char(char *str)
{
	char	*plus_char;

	plus_char = ft_strchr(str, '+');
	if (plus_char)
		ft_memmove(plus_char, plus_char + 1, ft_strlen(plus_char));
}

char	*prepare_env_var(char *var)
{
	char	*new_var;

	new_var = NULL;
	new_var = ft_strdup(var);
	if (new_var == NULL)
		return (NULL);
	return (new_var);
}
