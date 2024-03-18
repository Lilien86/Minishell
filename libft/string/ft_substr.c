/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:09:54 by lauger            #+#    #+#             */
/*   Updated: 2023/11/04 11:09:54 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*s_cpy;
	size_t	j;

	j = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		len = 0;
	else if (len >= ft_strlen(s) - start)
		len = ft_strlen(s + start);
	s_cpy = malloc((len + 1) * sizeof(char));
	if (!s_cpy)
		return (NULL);
	while (j < len)
	{
		s_cpy[j] = s[start];
		start++;
		j++;
	}
	s_cpy[j] = '\0';
	return (s_cpy);
}
