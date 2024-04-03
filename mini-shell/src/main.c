#include "minishell.h"

static size_t	env_len(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**copy_environment(char **env)
{
	char	**env_copy;
	size_t	i;
	size_t	env_size;

	env_size = env_len(env);
	env_copy = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
		{
			while (i > 0)
				free(env_copy[--i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = copy_environment(envp);
	if (!env)
		return (1);
	read_input(&env);
	ft_free_tab(env);
	return (0);
}
