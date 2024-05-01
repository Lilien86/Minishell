#include "../../minishell.h"

int	is_valid_var_name(const char *var)
{
	if (!ft_isalpha(*var) && *var != '_')
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (0);
		var++;
	}
	return (1);
}

int	is_valid_var_value(const char *value)
{
	(void)value;
	return (1);
}

int	handle_export_token(t_token *token, char ***env, int *env_size)
{
	if (!is_valid_var_name(token->value))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (0);
	}
	if (!process_export(token, env, env_size))
	{
		ft_putstr_fd(" malloc failed\n", 2);
		return (0);
	}
	return (1);
}
