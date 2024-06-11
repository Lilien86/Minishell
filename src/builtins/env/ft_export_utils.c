/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:31:15 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 09:59:00 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_var_name(const char *var, t_minishell *shell)
{
	shell->is_plus_equal = 0;
	if (!var || !(*var == '_' || ft_isalpha(*var)))
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			if (*var == '+' && *(var + 1) == '=')
				shell->is_plus_equal = 1;
			else
				return (0);
		}
		var++;
	}
	return (1);
}

char	*handle_plus_equal(char *env_var, char *var)
{
	char	*eq_pos;
	char	*value_to_add;
	char	*existing_value;
	char	*new_value;
	size_t	existing_value_len;

	eq_pos = ft_strchr(var, '=');
	if (eq_pos != NULL)
		value_to_add = eq_pos + 1;
	else
		value_to_add = "";
	existing_value = ft_strchr(env_var, '=');
	if (existing_value != NULL)
		existing_value += 1;
	else
		existing_value = "";
	existing_value_len = ft_strlen(existing_value);
	new_value = malloc(existing_value_len + ft_strlen(value_to_add) + 1);
	if (new_value == NULL)
	{
		return (NULL);
	}
	ft_strcpy(new_value, existing_value);
	ft_strcat(new_value, value_to_add);
	return (new_value);
}

char	**free_and_return(char *var_to_free, char **var_to_return)
{
	free(var_to_free);
	return (var_to_return);
}

char	**add_new_env_var(char *var, char ***env, t_minishell *shell)
{
	char	**new_env;
	char	*prepared_var;
	int		var_len;
	char	*eq_plus;

	prepared_var = prepare_env_var(var);
	if (prepared_var == NULL)
		return (NULL);
	eq_plus = ft_strchr(var, '+');
	if (eq_plus && *(eq_plus + 1) == '=')
		var_len = length_until_plus_equal(var);
	else
		var_len = length_until_equal(var);
	if (update_existing_var(prepared_var, env, var_len, shell))
		return (free_and_return(prepared_var, *env));
	new_env = create_new_env_array(prepared_var, env, shell);
	free(prepared_var);
	if (new_env == NULL)
		return (NULL);
	(shell->env_size)++;
	ft_free_tab(*env);
	*env = new_env;
	return (new_env);
}

int	handle_export_token(t_token *token, char ***env, t_minishell *shell)
{
	(void)shell;
	if (!is_valid_var_name(token->value, shell))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (0);
	}
	if (!process_export(token, env, shell))
	{
		ft_putstr_fd(" malloc failed\n", 2);
		return (0);
	}
	return (1);
}
