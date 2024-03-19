/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:06:28 by lauger            #+#    #+#             */
/*   Updated: 2024/01/08 14:03:15 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_base(char *base);

int	ft_putnbr_base_len(unsigned long int nbr, char *base)
{
	int					cnt_char;
	int					cnt;
	unsigned long int	l_nbr;

	cnt = 0;
	cnt_char = 0;
	l_nbr = (unsigned long int)nbr;
	if (check_base(base) == 0)
		return (0);
	while (base[cnt])
		cnt++;
	if (l_nbr < (unsigned long int)cnt)
	{
		write(1, &base[l_nbr], 1);
		cnt_char++;
	}
	else
	{
		cnt_char += ft_putnbr_base_len(l_nbr / cnt, base);
		cnt_char += ft_putnbr_base_len(l_nbr % cnt, base);
	}
	return (cnt_char);
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
