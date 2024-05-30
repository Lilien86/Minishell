/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitute_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:05 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/30 10:06:53 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_char_to_strfree(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

static void	normalize_characters(const char *str, char *result)
{
	int	i;
	int	j;
	int	in_space;

	i = 0;
	j = 0;
	in_space = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
		{
			if (in_space && j > 0)
				result[j++] = ' ';
			in_space = 0;
			result[j++] = str[i];
		}
		else
			in_space = 1;
		i++;
	}
	result[j] = '\0';
}

char	*normalize_spaces(char *str)
{
	char	*result;

	result = ft_calloc(strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	normalize_characters(str, result);
	return (result);
}
