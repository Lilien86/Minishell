/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:10:14 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/30 10:17:55 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_copy_tab(char **tab)
{
	char	**tab_copy;
	size_t	i;
	size_t	tab_size;

	tab_size = ft_tab_len(tab);
	tab_copy = (char **)ft_calloc(sizeof(char *), (tab_size + 1));
	if (!tab_copy)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tab_copy[i] = ft_strdup(tab[i]);
		if (!tab_copy[i])
		{
			while (i > 0)
				free(tab_copy[--i]);
			free(tab_copy);
			return (NULL);
		}
		i++;
	}
	tab_copy[i] = NULL;
	return (tab_copy);
}
