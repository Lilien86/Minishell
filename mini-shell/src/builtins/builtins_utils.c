#include "../minishell.h"

/**
 * @brief Checks if a string is the "-n" flag.
 * 
 * @param str The string to check.
 * @return 1 if the string is the "-n" flag, 0 otherwise.
 */
int	is_flag_n(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (1);
	return (0);
}

/**
 * @brief Retrieves the value of an environment variable.
 * 
 * @param name The name of the environment variable.
 * @param env The array of environment variables.
 * @return The value of the environment variable, or NULL if not found.
 */
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
