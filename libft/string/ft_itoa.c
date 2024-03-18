/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:50:37 by lauger            #+#    #+#             */
/*   Updated: 2023/11/07 14:29:24 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill(char *str, int idx, int integer);
static int	int_len(int i);

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*p;

	len = int_len(n);
	p = ft_calloc(len + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		i = 0;
		while (i < 11)
		{
			p[i] = "-2147483648"[i];
			i++;
		}
		return (p);
	}
	if (n == 0)
		p[0] = '0';
	else
		fill(p, len - 1, n);
	p[len] = '\0';
	return (p);
}

static void	fill(char *str, int idx, int n)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[idx] = '0' + (n % 10);
	n /= 10;
	if (n != 0)
		fill(str, idx - 1, n);
}

static int	int_len(int i)
{
	int	len;

	if (i == 0)
		return (1);
	len = 0;
	if (i < 0)
		len++;
	while (i != 0)
	{
		len++;
		i /= 10;
	}
	return (len);
}
