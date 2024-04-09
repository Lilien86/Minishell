#include "../minishell.h"

void	ft_echo(t_token *tokens, int *exit_status)
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
		if (ft_printf("%s", current->value) < 0)
		{
			perror("echo command failed");
			*exit_status = 1;
			return ;
		}
		current = current->next;
	}
	if (newline)
		ft_printf("\n");
	*exit_status = 0;
}

void	ft_cd(t_token *tokens, char **env, int *exit_status)
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
		*exit_status = 1;
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		*exit_status = 1;
	}
	else
		*exit_status = 0;
}

void	ft_pwd(int *exit_status)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		*exit_status = 0;
	}
	else
	{
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		*exit_status = 1;
	}
}
