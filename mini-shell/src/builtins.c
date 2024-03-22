#include "minishell.h"


static int	is_flag_n(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (1);
	return (0);
}

void	ft_echo(t_token *tokens)
{
	int		newline;
	t_token	*current;

	newline = 1;
	current = tokens->next; 

	while (current && is_flag_n(current->value))
	{
		newline = 0;
		current = current->next;
	}
	while (current != NULL)
	{
		ft_printf("%s", current->value);
		current = current->next;
	}

	if (newline)
		ft_printf("\n");
}

void	ft_cd(t_token *tokens, char **env)
{
	char	*path;
	int		ret;

	if (tokens->next == NULL)
		path = ft_getenv("HOME", env);
	else
		path = tokens->next->value;

	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
	}
}

char	*ft_getenv(const char *name, char **env)
{
    size_t name_len = strlen(name);
    for (int i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
            return &env[i][name_len + 1];
    }
    return NULL;
}
