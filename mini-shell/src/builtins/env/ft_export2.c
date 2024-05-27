#include "../../minishell.h"

int	is_valid_var_name(const char *var, t_minishell *shell)
{
	shell->is_plus_equal = 0;
	if (!var || !(*var == '_' || ft_isalpha(*var)))
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			if (*var == '+' && *(var + 1) == '=')
				shell->is_plus_equal = 1;
			else
				return (0);
		}
		var++;
	}
	return (1);
}

char	*handle_plus_equal(char *env_var, char *var)
{
	char	*eq_pos;
	char	*value_to_add;
	char	*existing_value;
	char	*new_value;

	eq_pos = ft_strchr(var, '=');
	if (eq_pos != NULL)
		value_to_add = eq_pos + 1;
	else
		value_to_add = "";
	if (ft_strchr(env_var, '='))
	{
		existing_value = ft_strchr(env_var, '=') + 1;
		if (existing_value == NULL)
			return (NULL);
	}
	else
		return (NULL);
	new_value = malloc(ft_strlen(existing_value) + ft_strlen(value_to_add) + 1);
	if (new_value == NULL)
		return (NULL);
	ft_strcpy(new_value, existing_value);
	ft_strcat(new_value, value_to_add);
	return (new_value);
}

int	handle_export_token(t_token *token, char ***env, t_minishell *shell)
{
	(void)shell;
	if (!is_valid_var_name(token->value, shell))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (0);
	}
	if (!process_export(token, env, shell))
	{
		ft_putstr_fd(" malloc failed\n", 2);
		return (0);
	}
	return (1);
}
