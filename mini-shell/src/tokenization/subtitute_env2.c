#include "../minishell.h"

char *process_dollar(const char **input, char **env, char *result, t_minishell *shell)
{
    char *temp;
    int var_len;

    temp = substitute_var(*input, env, shell);


    char *new_result = malloc(ft_strlen(result) + ft_strlen(temp) + 1);
    if (!new_result) return NULL;
    ft_strcpy(new_result, result);
    ft_strcat(new_result, temp);
    free(result);
    free(temp);

    var_len = var_length(*input + 1, shell) + 1; 
	if (*(*input + var_len) != '\0') {
	    *input += var_len;
	} else {
	    *input += ft_strlen(*input); // pour éviter de dépasser la fin de la chaîne
	}
    return new_result;
}

char	*substitute_env_vars(const char *input, char **env, t_minishell *shell)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && (i == 0))
			result = process_single_quote(&input, result, shell);
		else if (input[i] == '$' && (i == 0) \
		&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'
				|| input[i + 1] == '?'))
		{
			result = process_dollar(&input, env, result, shell);
			if (!result)
				return (NULL);
			return (result);
		}
		else
		{
			temp = append_char_to_str(result, input[i]);
			free(result);
			result = temp;
		}
		i++;
	}
	return (result);
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

char	*process_single_quote(const char **input, char *result,
			t_minishell *shell)
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
