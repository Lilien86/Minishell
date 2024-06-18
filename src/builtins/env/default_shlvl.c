/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_shlvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:25:08 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 14:35:59 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_shlvl_index(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (strncmp((*env)[i], "SHLVL=", 6) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	increment_existing_shlvl(char ***env)
{
	int		shlvl_index;
	int		shlvl;
	char	*shlvl_str;
	char	*new_shlvl_str;
	char	*shlvl_itoa;

	shlvl_index = find_shlvl_index(env);
	if (shlvl_index != -1)
	{
		shlvl_str = (*env)[shlvl_index] + 6;
		shlvl = ft_atoi(shlvl_str);
		shlvl_itoa = ft_itoa(++shlvl);
		new_shlvl_str = ft_strjoin("SHLVL=", shlvl_itoa);
		free(shlvl_itoa);
		if (new_shlvl_str != NULL)
		{
			free((*env)[shlvl_index]);
			(*env)[shlvl_index] = new_shlvl_str;
			return (1);
		}
	}
	return (0);
}

void	increment_shlvl(char ***env)
{
	int		new_shlvl_assigned;
	char	*new_shlvl_str;
	int		env_size;
	char	**new_env;

	new_shlvl_assigned = increment_existing_shlvl(env);
	if (!new_shlvl_assigned)
	{
		new_shlvl_str = ft_strdup("SHLVL=1");
		if (new_shlvl_str != NULL)
		{
			env_size = 0;
			while ((*env)[env_size] != NULL)
				env_size++;
			new_env = realloc(*env, (env_size + 2) * sizeof(char *));
			if (new_env != NULL)
			{
				new_env[env_size] = new_shlvl_str;
				new_env[env_size + 1] = NULL;
				*env = new_env;
			}
			else
				free(new_shlvl_str);
		}
	}
}
