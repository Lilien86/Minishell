#include "../../minishell.h"

void	ft_unset(t_token *tokens, char ***env)
{
	int		i;
	t_token	*current;

	current = tokens->next;
	while (current)
	{
		i = 0;
		while ((*env)[i])
		{
			if (strncmp((*env)[i], current->value, strlen(current->value))
				== 0 && (*env)[i][strlen(current->value)] == '=')
			{
				free((*env)[i]);
				while ((*env)[i + 1])
				{
					(*env)[i] = (*env)[i + 1];
					i++;
				}
				(*env)[i] = NULL;
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

void	ft_env(char **env)
{
	int		i;
	char	*equal_sign_ptr;

	i = 0;
	while (env[i] != NULL)
	{
		equal_sign_ptr = ft_strchr(env[i], '=');
		if (equal_sign_ptr != NULL && *(equal_sign_ptr + 1) != '\0')
		{
			if (!(*(equal_sign_ptr + 1) == '\''
					&& *(equal_sign_ptr + 2) == '\''
					&& *(equal_sign_ptr + 3) == '\0'))
			{
				ft_printf("%s\n", env[i]);
			}
		}
		i++;
	}
}
