/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:03:11 by lauger            #+#    #+#             */
/*   Updated: 2024/05/24 12:26:05 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t		len;
	const char	*ptr;
	char		*dup;
	size_t		i;

	len = 0;
	ptr = src;
	i = 0;
	while (len < n && *ptr != '\0')
	{
		len++;
		ptr++;
	}
	dup = (char *)ft_calloc((len + 1), sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
