#include "../minishell.h"

int	is_flag_n(char *str)
{
	int i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*ft_getenv(const char *name, char **env)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (&env[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	ft_sort_string_tab(env);
	while (env[i])
	{
		ft_printf("declare -x %s\n", env[i]);
		i++;
	}
}

int	length_until_equal(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

int	process_export(t_token *tokens, char ***env, int *env_size)
{
	char	**new_env;

	while (tokens)
	{
		new_env = add_new_env_var(tokens->value, env, env_size);
		if (!new_env)
			return (0);
		*env = new_env;
		tokens = tokens->next;
	}
	return (1);
}
