#include "minishell.h"

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
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
	}
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	else
		ft_printf("minishell: pwd: %s\n", strerror(errno));
}
