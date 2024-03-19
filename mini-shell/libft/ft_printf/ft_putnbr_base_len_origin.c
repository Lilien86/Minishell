/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_len_origin.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:12:46 by lauger            #+#    #+#             */
/*   Updated: 2023/11/16 08:53:04 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_base(char *base);

int	ft_putlnbr(int nbr)
{
	int	cnt;

	cnt = 0;
	if (nbr < 0)
		cnt++;
	if (nbr == 0)
		cnt++;
	while (nbr)
	{
		nbr = nbr / 10;
		cnt++;
	}
	return (cnt);
}

int	ft_putnbr_base_len_origin(int nbr, char *base)
{
	int			cnt;
	long long	l_nbr;

	cnt = 0;
	l_nbr = (long long)nbr;
	if (check_base(base) == 0)
		return (0);
	while (base[cnt])
		cnt++;
	if (l_nbr < 0)
	{
		write(1, "-", 1);
		l_nbr = -l_nbr;
	}
	if (l_nbr < (long long)cnt)
	{
		write(1, &base[l_nbr], 1);
	}
	else
	{
		ft_putnbr_base_len_origin(l_nbr / cnt, base);
		ft_putnbr_base_len_origin(l_nbr % cnt, base);
	}
	return (ft_putlnbr(nbr));
}

static int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i] != '\0')
	{
		j = i +1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j] || (base[i] == '-' || base[i] == '+'))
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
