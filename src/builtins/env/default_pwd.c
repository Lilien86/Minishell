/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:12:23 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 14:26:15 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_pwd_assigned(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (strncmp((*env)[i], "PWD=", 4) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*create_pwd_str(void)
{
	char	*cwd;
	char	*pwd_str;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	pwd_str = ft_strjoin("PWD=", cwd);
	free(cwd);
	return (pwd_str);
}

void	add_pwd_to_env(char ***env, char *pwd_str)
{
	int		env_size;
	char	**new_env;

	env_size = 0;
	while ((*env)[env_size] != NULL)
		env_size++;
	new_env = realloc(*env, (env_size + 2) * sizeof(char *));
	if (new_env != NULL)
	{
		new_env[env_size] = pwd_str;
		new_env[env_size + 1] = NULL;
		*env = new_env;
	}
	else
		free(pwd_str);
}

void	set_pwd_if_not_defined(char ***env)
{
	char	*pwd_str;

	if (!is_pwd_assigned(env))
	{
		pwd_str = create_pwd_str();
		if (pwd_str != NULL)
			add_pwd_to_env(env, pwd_str);
	}
}
