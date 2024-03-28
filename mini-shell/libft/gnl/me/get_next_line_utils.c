/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:40:21 by lauger            #+#    #+#             */
/*   Updated: 2024/03/28 11:03:38 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Concatenates two strings.
 *
 * This function concatenates two strings, `s1` and `s2`, into a newly allocated string.
 * The resulting string is created by dynamically allocating memory using `malloc`.
 * It calculates the total length of `s1` and `s2`, allocates memory for the concatenated string,
 * and then copies the characters from `s1` and `s2` into the new string.
 * Finally, it frees the memory allocated for `s1` and returns the concatenated string.
 *
 * @param s1 The first string to be concatenated.
 * @param s2 The second string to be concatenated.
 * @return The concatenated string, or NULL if memory allocation fails.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	str = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	free(s1);
	str[j] = 0;
	return (str);
}

int	check_str_char(char *line, char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
	{
		i++;
		while (line[i])
		{
			buffer[j] = line[i];
			j++;
			i++;
		}
		buffer[j] = '\0';
		line[i - j] = 0;
		return (1);
	}
	return (0);
}
