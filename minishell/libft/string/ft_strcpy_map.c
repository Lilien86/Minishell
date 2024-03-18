/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 07:31:21 by lilien            #+#    #+#             */
/*   Updated: 2024/01/06 09:56:03 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dest, const char *src)
{
	if (dest == NULL || src == NULL)
		return ;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

char	**ft_strcpy_map(char **original, int height, int width)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = ft_calloc(height + 1, sizeof(char *));
	while (i < height)
	{
		cpy[i] = ft_calloc((width + 1), sizeof(char));
		ft_strcpy(cpy[i], original[i]);
		i++;
	}
	return (cpy);
}
