/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:50:58 by ybarbot           #+#    #+#             */
/*   Updated: 2024/05/30 09:45:56 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void sort_and_print_env(char **env, int env_size)
{
	int		i;
	char	*eq;
	int		index;

	(void)env_size;
	ft_sort_string_tab(env);
	i = 0;
	while (env[i])
	{
		if (!(env[i][0] == '_' && env[i][1] == '='))
		{
			eq = ft_strchr(env[i], '=');
			if (eq)
			{
				index = (int)(eq - env[i]);
				printf("declare -x %.*s=\"%s\"\n", \
					index, env[i], env[i] + index + 1);
			}
			else
				printf("declare -x %s\n", env[i]);
		}
		i++;
	}
}

void	print_env(char **env)
{
	int		env_size;
	char	**temp_env;

	env_size = 0;
	while (env[env_size])
		env_size++;
	temp_env = ft_copy_tab(env);
	if (temp_env == NULL)
		return ;
	sort_and_print_env(temp_env, env_size);
	ft_free_tab(temp_env);
}
