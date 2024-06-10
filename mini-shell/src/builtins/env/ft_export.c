/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:30:30 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/10 19:06:38 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	update_with_plus_equal(char *var, int var_len, int i,
		t_minishell *shell)
{
	char	*new_value;
	char	*key;
	char	*concatened_value;

	new_value = handle_plus_equal(shell->env[i], var);
	if (!new_value)
		return (0);
	key = ft_strndup(var, (size_t)var_len);
	concatened_value = ft_calloc((size_t)var_len + 1
			+ ft_strlen(new_value) + 1, sizeof(char*));
	if (!concatened_value)
	{
		free(new_value);
		free(key);
		return (0);
	}
	ft_strcpy(concatened_value, key);
	ft_strcat(concatened_value, "=");
	ft_strcat(concatened_value, new_value);
	free(new_value);
	free(shell->env[i]);
	shell->env[i] = ft_strdup(concatened_value);
	free(concatened_value);
	free(key);
	return (1);
}

int	update_existing_var(char *var, char ***env,
			int var_len, t_minishell *shell)
{
	int		i;
	char	*eq;

	i = 0;
	while (i < shell->env_size)
	{
		if ((*env)[i] != NULL && ft_strncmp((*env)[i], var,
			(size_t)var_len) == 0)
		{
			if (shell->is_plus_equal == 1)
				return (update_with_plus_equal(var, var_len, i, shell));
			eq = ft_strchr(var, '=');
			if (!eq || (*(eq + 1) == '\0' && eq != &var[ft_strlen(var) - 1]))
				return (1);
			free((*env)[i]);
			(*env)[i] = ft_strdup(var);
			if (!(*env)[i])
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

static	char	**copy_env_to_array(char ***env, t_minishell *shell)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * ((size_t)(shell->env_size) + 2));
	if (!array)
		return (NULL);
	i = 0;
	while (i < shell->env_size)
	{
		array[i] = ft_strdup((*env)[i]);
		if (!array[i])
		{
			ft_free_tab(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}

char	**create_new_env_array(char *var, char ***env, t_minishell *shell)
{
	char	**array;
	int		i;

	array = copy_env_to_array(env, shell);
	if (!array)
		return (NULL);
	i = shell->env_size;
	if (shell->is_plus_equal == 1)
		remove_plus_char(var);
	array[i] = ft_strdup(var);
	if (!array[i])
	{
		ft_free_tab(array);
		return (NULL);
	}
	array[i + 1] = NULL;
	return (array);
}

void	ft_export(t_token *tokens, char ***env,
		int *exit_status, t_minishell *shell)
{
	shell->env_size = 0;
	if (!tokens->next)
	{
		print_env(*env);
		*exit_status = 0;
		return ;
	}
	while ((*env)[shell->env_size])
		shell->env_size++;
	tokens = tokens->next;
	while (tokens)
	{
		if (!handle_export_token(tokens, env, shell))
		{
			*exit_status = 1;
			return ;
		}
		tokens = tokens->next;
	}
	*exit_status = 0;
}
