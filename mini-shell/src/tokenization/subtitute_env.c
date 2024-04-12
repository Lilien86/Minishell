#include "../minishell.h"

int	var_length(const char *str, t_minishell *shell)
{
	int	len;

	(void)shell;
	len = 0;
	if (*str == '?')
		return (1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

char	*copy_env_value(char *key, char **env, t_minishell *shell)
{
	char	*value;

	(void)shell;
	value = ft_getenv(key, env);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

char *substitute_var(const char *input, char **env, t_minishell *shell)
{
	if (input[0] == '$' && input[1] == '?') {
		char *exit_status_str = malloc(12); // Large enough for any int
		if (!exit_status_str) return NULL;
		sprintf(exit_status_str, "%d", shell->exit_status);
		return exit_status_str;
	}

	// Original functionality for other variables
	int len = var_length(input, shell);
	char *key = ft_strndup(input, (size_t)len);
	if (!key) return NULL;
	char *substituted_value = copy_env_value(key, env, shell);
	free(key);
	return substituted_value;
}


char	*append_char_to_str(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*process_single_quote(const char **input, char *result, t_minishell *shell)
{
	char	*temp;
	int		start;
	char	*to_free;

	(void)shell;
	start = (int)(*input - result);
	(*input)++;
	while (**input && **input != '\'')
		(*input)++;
	temp = ft_substr(result, (unsigned int)start,
			(size_t)((*input) - result - start));
	to_free = result;
	result = ft_strjoin(result, temp);
	free(temp);
	return (result);
}
