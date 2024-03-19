/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:12:53 by lauger            #+#    #+#             */
/*   Updated: 2023/11/01 15:29:31 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			cnt;
	unsigned char	*temp;
	unsigned char	c_cpy;

	temp = (unsigned char *)dest;
	c_cpy = (unsigned char)c;
	cnt = 0;
	while (cnt < n)
	{
		temp[cnt] = c_cpy;
		cnt++;
	}
	return (dest);
}
