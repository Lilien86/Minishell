/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitute_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:16:37 by ybarbot           #+#    #+#             */
/*   Updated: 2024/04/09 10:49:49 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static int var_length(const char *str)
{
	int len;

	len = 0;
	if (*str == '?')
		return 1;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return len;
}

// Substitute variable with its value from the environment
char *substitute_var(const char *input, char **env)
{
	int len = var_length(input);
	char *key = ft_strndup(input, (size_t)len); 
	char *value = ft_getenv(key, env);
	free(key);
	return value ? ft_strdup(value) : ft_strdup("");
}

// Main substitution function
char *substitute_env_vars(const char *input, char **env)
{
	char *result = ft_strdup("");
	char *temp;
	char *to_free;
	for (int i = 0; input[i]; i++)
	{
		if (input[i] == '\'' && (i == 0 || input[i - 1] != '\\'))
		{
			int start = ++i;
			while (input[i] && input[i] != '\'') i++;
			temp = ft_substr(input, (unsigned int)start, (size_t)(i - start));
			to_free = result;
			result = ft_strjoin(result, temp);
			free(temp);
			free(to_free);
		}
		else if (input[i] == '$' && (i == 0 || input[i - 1] != '\\') &&
				 (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
		{
			i++;
			temp = substitute_var(input + i, env);
			to_free = result;
			result = ft_strjoin(result, temp);
			free(temp);
			free(to_free);
			i += var_length(input + i) - 1;
		}
		else
		{
			int len = (int)ft_strlen(result);
			temp = malloc(sizeof(char) * (size_t)(len + 2)); 
			ft_strncpy(temp, result, (size_t)len);
			temp[len] = input[i];
			temp[len + 1] = '\0';
			free(result);
			result = temp;
		}
	}
	return result;
}