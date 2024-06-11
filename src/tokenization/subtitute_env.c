/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitute_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:13 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/03 11:06:34 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_length(const char *str, t_minishell *shell)
{
	int	len;

	(void)shell;
	len = 0;
	if (*str == '?')
		return (1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

char	*copy_env_value(char *key, char **env, t_minishell *shell)
{
	char	*value;

	(void)shell;
	value = ft_getenv(key, env);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

static char	*get_exit_status_str(int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	return (status_str);
}

static char	*get_env_var(const char *input, char **env, t_minishell *shell)
{
	int		len;
	char	*key;
	char	*value;

	len = var_length(input, shell);
	key = ft_strndup(input, (size_t)len);
	if (!key)
		return (NULL);
	value = ft_getenv(key, env);
	free(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*substitute_var(const char *input, char **env, t_minishell *shell)
{
	if (input[0] == '$')
	{
		if (input[1] == '?')
		{
			if (g_exit_signal != 0)
				return (get_exit_status_str(g_exit_signal));
			else
				return (get_exit_status_str(shell->exit_status));
		}
		input++;
		return (get_env_var(input, env, shell));
	}
	return (ft_strdup(input));
}
