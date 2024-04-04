#include "../minishell.h"

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
			if (!new_var)
				return (0);
			(*env)[i] = ft_strjoin(new_var, value);
			if (!(*env)[i])
			{
				free(new_var);
				return (0);
			}
			free(new_var);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	create_new_env_var(char *key, char *value, char **env_var)
{
	char *new_var;

	new_var = ft_strjoin(key, "=");
	if (!new_var)
		return ;
	*env_var = ft_strjoin(new_var, value);
	if (!*env_var)
	{
		free(new_var);
		return ;
	}
	free(new_var);
}

static void	insert_env_var(char ***env, char *env_var, size_t env_size)
{
	char **new_env;

	new_env = ft_realloc(*env, sizeof(char *) * (env_size + 1),
			 sizeof(char *) * (env_size + 2));
	if (!new_env)
	{
		free(env_var);
		return;
	}
	new_env[env_size] = env_var;
    new_env[env_size + 1] = NULL;
    *env = new_env;
}

static void	add_new_env_var(char *arg, char ***env, size_t env_size)
{
	char **split_arg;
	char *key;
	char *value;
	char *env_var;

	split_arg = ft_split(arg, '=');
	if (!split_arg || !split_arg[0])
	{
		ft_free_tab(split_arg);
		return ;
	}
	key = split_arg[0];
	if (split_arg[1])
		value = split_arg[1];
	else
		value = "";
	if (!update_env_var(key, value, env))
	{
		create_new_env_var(key, value, &env_var);
		insert_env_var(env, env_var, env_size);
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
