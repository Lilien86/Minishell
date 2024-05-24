#include "../../minishell.h"

static int	update_existing_var(char *var, char ***env, int var_len, t_minishell *shell)
{
	int	i;
	char *eq;
	char *new_value;
	char *key;
	char *concatened_value;

	i = 0;
	while (i < shell->env_size)
	{
		if ((*env)[i] != NULL && ft_strncmp((*env)[i], var,
		(size_t)var_len) == 0)
		{
			if (shell->is_plus_equal == 1)
			{
				new_value = handle_plus_equal((*env)[i], var);
				if (!new_value)
					return (0);
				key = ft_strndup(var, (size_t)var_len);
				concatened_value = ft_calloc((size_t)var_len + 1 + ft_strlen(new_value) + 1, sizeof(char*));
				ft_strcpy(concatened_value, key);
				ft_strcat(concatened_value, "=");
				ft_strcat(concatened_value, new_value);
				free(new_value);
				free((*env)[i]);
				(*env)[i] = ft_strdup(concatened_value);
				free(concatened_value);
				free(key);
				return (1);
			}
			eq = ft_strchr(var, '=');
			if (!eq || *(eq + 1) == '\0' && eq != &var[ft_strlen(var) - 1])
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

char *handle_plus_equal(char *env_var, char *var)
{
	char *eq_pos;
    char *value_to_add;
	char *existing_value;
    char *new_value;

	eq_pos = ft_strchr(var, '=');
	if (eq_pos != NULL)
        value_to_add = eq_pos + 1;
    else
        value_to_add = "";
	if (ft_strchr(env_var, '='))
	{
    	existing_value = ft_strchr(env_var, '=') + 1;
		if (existing_value == NULL)
			return (NULL);
	}
	else
		return (NULL);
    new_value = malloc(ft_strlen(existing_value) + ft_strlen(value_to_add) + 1);
    if (new_value == NULL)
        return (NULL);
    ft_strcpy(new_value, existing_value);
    ft_strcat(new_value, value_to_add);
    return new_value;
}

static char	**create_new_env_array(char *var, char ***env, t_minishell *shell)
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
	if (shell->is_plus_equal == 1)
	{
		remove_plus_char(var);
	}
	array[i] = ft_strdup(var);
	if (!array[i])
	{
		ft_free_tab(array);
		return (NULL);
	}
	array[i + 1] = NULL;
	return (array);
}

static char	*prepare_env_var(char *var)
{
	char	*new_var;

	new_var = NULL;
	new_var = ft_strdup(var);
	if (new_var == NULL)
		return (NULL);
	return (new_var);
}

char	**add_new_env_var(char *var, char ***env, t_minishell *shell)
{
	char	**new_env;
	char	*prepared_var;
	int		var_len;
	char 	*eq_plus;

	prepared_var = prepare_env_var(var);
	if (prepared_var == NULL)
		return (NULL);
	eq_plus = ft_strchr(var, '+');
	if (eq_plus && *(eq_plus + 1) == '=')
		var_len = length_until_plus_equal(var);
	else
		var_len = length_until_equal(var);
	if (update_existing_var(prepared_var, env, var_len, shell))
	{
		free(prepared_var);
		return (*env);
	}
	new_env = create_new_env_array(prepared_var, env, shell);
	free(prepared_var);
	if (new_env == NULL)
		return (NULL);
	(shell->env_size)++;
	ft_free_tab(*env);
	*env = new_env;
	return (new_env);
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
