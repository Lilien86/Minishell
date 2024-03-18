/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:21:54 by lauger            #+#    #+#             */
/*   Updated: 2023/11/05 11:26:22 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searchedChar)
{
	int	cnt;

	cnt = 0;
	if (str == NULL)
		return (0);
	while (str[cnt])
		cnt++;
	while (cnt >= 0)
	{
		if (str[cnt] == (char)searchedChar)
			return ((char *)(str + cnt));
		cnt--;
	}
	return (0);
}
