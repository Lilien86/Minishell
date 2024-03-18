/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:50:19 by marvin            #+#    #+#             */
/*   Updated: 2023/11/04 14:50:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkchar(const char c, const char *set)
{
	int	cnt;

	cnt = 0;
	while (set[cnt])
	{
		if (set[cnt] == c)
			return (1);
		cnt++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*p;
	size_t		start;
	size_t		end;
	size_t		cnt;

	start = 0;
	end = ft_strlen(s1) - 1;
	cnt = 0;
	while (ft_checkchar(s1[start], set) == 1)
		start++;
	while (ft_checkchar(s1[end], set) == 1 && start < ft_strlen(s1))
		end--;
	p = malloc (sizeof(char) * (end - start + 2));
	if (!p)
		return (NULL);
	while (s1[start] && start <= end)
	{
		p[cnt] = s1[start];
		cnt++;
		start++;
	}
	p[cnt] = '\0';
	return (p);
}
