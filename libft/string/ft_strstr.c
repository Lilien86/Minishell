/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:25:30 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/24 12:25:37 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	is_present;

	if (to_find[0] == '\0')
		return (str);
	j = 0;
	while (str[j])
	{
		i = 0;
		while (to_find[i])
		{
			if (to_find[i] != str[i + j])
			{
				is_present = 0;
				break ;
			}
			is_present = 1;
			i++;
		}
		if (is_present == 1)
			return (str + j);
		j++;
	}
	return (0);
}
