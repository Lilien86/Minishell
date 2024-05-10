/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:09:46 by ybarbot           #+#    #+#             */
/*   Updated: 2024/04/04 14:29:25 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t oldsize)
{
	void	*newptr;

	newptr = ft_calloc(1, size);
	if (!newptr)
		return (NULL);
	if (!ptr)
		return (newptr);
	if (size < oldsize)
		ft_memmove(newptr, ptr, size);
	else
		ft_memmove(newptr, ptr, oldsize);
	free (ptr);
	return (newptr);
}
