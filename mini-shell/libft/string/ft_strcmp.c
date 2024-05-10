/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:15:26 by ybarbot           #+#    #+#             */
/*   Updated: 2024/04/08 13:22:24 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	cmp_char(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (s1 != s2);
	while (s1[i] && s2[i])
	{
		if (cmp_char(s1[i], s2[i]) != 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (cmp_char(s1[i], s2[i]));
}
