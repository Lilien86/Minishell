/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:03:11 by lauger            #+#    #+#             */
/*   Updated: 2024/03/20 08:18:21 by lauger           ###   ########.fr       */
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
	dup = (char *)malloc((len + 1) * sizeof(char));
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
