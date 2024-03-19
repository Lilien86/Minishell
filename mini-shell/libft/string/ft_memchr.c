/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:11:47 by lauger            #+#    #+#             */
/*   Updated: 2023/11/01 15:06:07 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			cnt;
	unsigned char	*s_cpy;

	s_cpy = (unsigned char *) s;
	cnt = 0;
	while (cnt < n)
	{
		if (s_cpy[cnt] == (unsigned char) c)
			return (s_cpy + cnt);
		cnt++;
	}
	return (NULL);
}
