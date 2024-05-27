#include "../minishell.h"

char	*process_dollar(const char **input, char **env, char *result,
		t_minishell *shell)
{
	char	*temp;
	int		var_len;
	char	*new_result;

	temp = substitute_var(*input, env, shell);
	new_result = malloc(ft_strlen(result) + ft_strlen(temp) + 1);
	if (!new_result)
		return (NULL);
	ft_strcpy(new_result, result);
	ft_strcat(new_result, temp);
	free(temp);
	var_len = var_length(*input + 1, shell) + 1;
	*input += var_len;
	return (new_result);
}

char	*substitute_env_vars(const char *input, char **env, t_minishell *shell)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*input)
	{
		if (shell->is_single_quote != 1 && *input == '$'
			&& (ft_isalnum(*(input + 1)) \
			|| *(input + 1) == '_' || *(input + 1) == '?'))
			temp = process_dollar(&input, env, result, shell);
		else
			temp = append_char_to_str(result, *input++);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		if (result)
			free(result);
		result = temp;
	}
	return (result);
}

static char	*process_word(char *word, char **env,
				char *result, t_minishell *shell)
{
	char	*temp;

	while (*word)
	{
		if (shell->is_single_quote != 1 && *word == '$'
			&& (ft_isalnum(*(word + 1)) || *(word + 1) == '_'
				|| *(word + 1) == '?'))
			temp = process_dollar((const char **)&word, env, result, shell);
		else
			temp = append_char_to_str(result, *word++);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		free(result);
		result = temp;
	}
	return (result);
}

char	*substitute_env_vars_handle_quotes(char *word, char **env,
			t_minishell *shell)
{
	char	*result;
	char	*final_result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	final_result = process_word(word, env, result, shell);
	if (!final_result)
		return (NULL);

	word = ft_strdup(final_result);
	free(final_result);
	return (word);
}


char	*append_char_to_str(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = ft_calloc(sizeof(char), (len + 2));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
