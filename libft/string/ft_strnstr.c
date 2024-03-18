/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:39:11 by lauger            #+#    #+#             */
/*   Updated: 2023/11/05 11:03:36 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!little || !little[0])
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (*big && j < len)
	{
		i = 0;
		while (big[i] == little[i]
			&& little[i] != '\0' && j + i < len)
		{
			i++;
		}
		if (little[i] == '\0')
			return ((char *)big);
		big++;
		j++;
	}
	return (0);
}
