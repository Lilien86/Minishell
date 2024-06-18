/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:29:09 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 10:30:46 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_new_pwd(void)
{
	char	*current_pwd;
	char	*new_pwd;

	current_pwd = getcwd(NULL, 0);
	if (current_pwd != NULL)
	{
		new_pwd = ft_strjoin("PWD=", current_pwd);
		free(current_pwd);
		return (new_pwd);
	}
	return (NULL);
}

void	update_env_with_pwd(char **env, char *new_pwd)
{
	int		i;
	int		new_pwd_assigned;

	i = 0;
	new_pwd_assigned = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = new_pwd;
			new_pwd_assigned = 1;
			break ;
		}
		i++;
	}
	if (!new_pwd_assigned)
		free(new_pwd);
}
