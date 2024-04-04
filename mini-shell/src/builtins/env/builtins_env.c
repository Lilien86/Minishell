#include "../../minishell.h"

void ft_unset(t_token *tokens, char ***env)
{
    t_token *current = tokens->next;
    while (current)
    {
        int i = 0;
        while ((*env)[i])
        {
            if (strncmp((*env)[i], current->value, strlen(current->value)) == 0 && (*env)[i][strlen(current->value)] == '=')
            {
                free((*env)[i]);
                while ((*env)[i + 1])
                {
                    (*env)[i] = (*env)[i + 1];
                    i++;
                }
                (*env)[i] = NULL;
                break;
            }
            i++;
        }
        current = current->next;
    }
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (strchr(env[i], '=') != NULL)
		{
			ft_printf("%s\n", env[i]);
		}
		i++;
	}
}
