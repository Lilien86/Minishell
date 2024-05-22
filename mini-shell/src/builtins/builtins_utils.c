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
	int	j;
	char *eq;
	int index;

	i = 0;
	ft_sort_string_tab(env);
	while (env[i])
	{
		if (!(env[i][0] == '_' && env[i][1] == '='))
		{
			eq = ft_strchr(env[i], '=');
			if (eq)
			{
				index = (int)(eq - env[i]);
				printf("declare -x %.*s=\"%s\"\n", index, env[i], env[i] + index + 1);
			}
			else
				ft_printf("declare -x %s\n", env[i]);
		}
		i++;
	}
	// i = 0;
	// printf("\n\n\n");

	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
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
		if (tokens->value[0] == '_' && tokens->value[1] == '=')
			return (1);
		new_env = add_new_env_var(tokens->value, env, env_size);
		if (!new_env)
			return (0);
		*env = new_env;
		tokens = tokens->next;
	}
	return (1);
}
