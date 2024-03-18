/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:49:13 by lauger            #+#    #+#             */
/*   Updated: 2023/11/21 16:06:48 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_pointer(long long p)
{
	int	value;

	value = 0;
	if (p == 0)
	{
		write(1, "(nil)", 5);
		value = 5;
		return (value);
	}
	else
	{
		value = ft_putstr_len("0x");
		value += ft_putnbr_base_len(p, "0123456789abcdef");
		return (value);
	}
}

static int	ft_check_format(char *str, size_t i, va_list args)
{
	int	value;

	value = 0;
	if (str[i + 1] == 'c')
		value = ft_putchar(va_arg(args, int));
	else if (str[i + 1] == '%')
		value = ft_putchar('%');
	else if (str[i + 1] == 's')
		value = ft_putstr_len(va_arg(args, char *));
	else if (str[i + 1] == 'd' || str[i + 1] == 'i')
		value = ft_putnbr_base_len_origin
			(va_arg(args, int), "0123456789");
	else if (str[i + 1] == 'u')
		value = ft_putnbr_base_len
			(va_arg(args, unsigned int), "0123456789");
	else if (str[i + 1] == 'x')
		value = ft_putnbr_base_len
			(va_arg(args, unsigned int), "0123456789abcdef");
	else if (str[i + 1] == 'X')
		value = ft_putnbr_base_len
			(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (str[i + 1] == 'p')
		value = ft_check_pointer(va_arg(args, unsigned long int));
	return (value);
}

static void	ft_init(size_t *read, int *cnt_char)
{
	*read = 0;
	*cnt_char = 0;
}

int	ft_printf(const char *str, ...)
{
	size_t	read;
	va_list	args;
	int		cnt_char;

	va_start(args, str);
	ft_init(&read, &cnt_char);
	if (!str)
		return (-1);
	while (str[read])
	{
		if (str[read] == '%')
		{
			if (str[read + 1] == '\0')
				return (-1);
			cnt_char += ft_check_format((char *)str, read, args);
			read += 2;
		}
		else
		{
			write (1, &str[read++], 1);
			cnt_char++;
		}
	}
	va_end(args);
	return (cnt_char);
}
