#include "../minishell.h"

/**
 * @brief Prints the environment variables.
 *
 * This function prints the environment variables
 * in the format "declare -x VAR_NAME=VAR_VALUE".
 *
 * @param env The array of environment variables.
 */
static void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("declare -x %s\n", env[i]);
		i++;
	}
}

/**
 * @brief Updates an environment variable.
 *
 * This function updates the value of an existing 
 * environment variable or adds a new environment variable if it doesn't exist.
 *
 * @param key The key of the environment variable.
 * @param value The new value of the environment variable.
 * @param env A pointer to the array of environment variables.
 * @return 1 if the environment variable was updated, 0 otherwise.
 */
static int	update_env_var(char *key, char *value, char ***env)
{
	int		i;
	char	*new_var;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, 
			ft_strlen(key)) == 0 && (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			new_var = ft_strjoin(key, "=");
			(*env)[i] = ft_strjoin(new_var, value);
			free(new_var);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_new_env_var(char *arg, char ***env, size_t env_size)
{
	char	**split_arg;
	char	*key;
	char	*value;
	char	*new_var;
	char	**new_env;

	split_arg = ft_split(arg, '=');
	key = split_arg[0];
	if (split_arg[1])
		value = split_arg[1];
	else
		value = "";
	new_env = NULL;
	if (!update_env_var(key, value, env))
	{
		new_env = ft_realloc(*env, sizeof(char *) * (env_size + 1),
				sizeof(char *) * (env_size + 2));
		if (!new_env)
		{
			ft_free_tab(split_arg);
			return ;
		}
		*env = new_env;
		new_var = ft_strjoin(key, "=");
		(*env)[env_size] = ft_strjoin(new_var, value);
		(*env)[env_size + 1] = NULL;
		//free(new_var);
	}
	ft_free_tab(split_arg);
}

void	ft_export(t_token *tokens, char ***env)
{
	size_t	env_size;
	char	**temp_env;

	temp_env = *env;
	env_size = 0;
	while (temp_env[env_size])
		env_size++;
	if (!tokens->next)
	{
		print_env(*env);
		return ;
	}
	tokens = tokens->next;
	while (tokens)
	{
		add_new_env_var(tokens->value, env, env_size);
		tokens = tokens->next;
	}
}
