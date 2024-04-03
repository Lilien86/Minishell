#include "../../minishell.h"

static int	length_until_equal(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

static int	update_existing_var(char *var, char ***env, int var_len,
			int *env_size)
{
	int	i;

	i = 0;
	while (i < *env_size)
	{
		if ((*env)[i] != NULL && ft_strncmp((*env)[i], var,
		(size_t)var_len) == 0 && (*env)[i][var_len] == '=')
		{
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

static char	**create_new_env_array(char *var, char ***env, int *env_size)
{
	char	**array;
	int		i;

	array = (char **)malloc(sizeof(char *) * ((size_t)(*env_size) + 2));
	if (!array)
		return (NULL);
	i = 0;
	while (i < *env_size)
	{
		array[i] = ft_strdup((*env)[i]);
		if (!array[i])
		{
			ft_free_tab(array);
			return (NULL);
		}
		i++;
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

static char *prepare_env_var(char *var)
{
    char	*new_var;
    int		var_len;

    var_len = length_until_equal(var);
    if (var[var_len] != '=')
	{
        new_var = malloc(strlen(var) + 3);
        if (new_var == NULL)
            return (NULL);
        strcpy(new_var, var);
        strcat(new_var, "=''");
    }
	else
	{
        new_var = ft_strdup(var);
        if (new_var == NULL)
            return (NULL);
    }
    return (new_var);
}

static char **add_new_env_var(char *var, char ***env, int *env_size)
{
    char	**new_env;
    char	*prepared_var;
    int		var_len;

    prepared_var = prepare_env_var(var);
    if (prepared_var == NULL)
        return (NULL);

    var_len = length_until_equal(prepared_var);
    if (update_existing_var(prepared_var, env, var_len, env_size))
	{
        free(prepared_var);
        return (*env);
    }

    new_env = create_new_env_array(prepared_var, env, env_size);
    free(prepared_var);

    if (new_env == NULL)
        return (NULL);

    (*env_size)++;
    ft_free_tab(*env);
    *env = new_env;
    return (new_env);
}


void	ft_export(t_token *tokens, char ***env)
{
	int		env_size;
	char	**new_env;

	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	if (!tokens->next)
	{
		print_env(*env);
		return ;
	}
	tokens = tokens->next;
	while (tokens)
	{
		new_env = add_new_env_var(tokens->value, env, &env_size);
		if (!new_env)
			return ;
		*env = new_env;
		tokens = tokens->next;
	}
}
