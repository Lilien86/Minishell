/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:31:26 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/10 20:05:06 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag_n(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*ft_getenv(const char *name, char **env)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (&env[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

int	length_until_equal(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

int	process_export(t_token *tokens, char ***env, t_minishell *shell)
{
	char	**new_env;

	while (tokens)
	{
		if (tokens->value[0] == '_' && tokens->value[1] == '=')
			return (1);
		new_env = add_new_env_var(tokens->value, env, shell);
		if (!new_env)
			return (0);
		*env = new_env;
		tokens = tokens->next;
	}
	return (1);
}
