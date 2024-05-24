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
