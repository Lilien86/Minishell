#include "../minishell.h"

char	*process_dollar(const char **input, char **env, char *result,
			t_minishell *shell)
{
	char	*temp;
	char	*to_free;

	temp = substitute_var(*input, env, shell);
	to_free = result;
	result = ft_strjoin(result, temp);
	free(temp);
	(*input) += var_length(*input, shell) + 1;
	return (result);
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
			result = process_dollar(&input, env, result, shell);
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
