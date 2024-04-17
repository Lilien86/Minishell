#include "../minishell.h"

void	echo_print_tokens(t_token *tokens, int *exit_status,
			int newline, t_minishell *shell)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_WORD)
		{
			if (ft_printf("%s", current->value) < 0)
			{
				perror("echo command failed");
				*exit_status = 1;
				return ;
			}
		}
		else if (shell->space_flag == 1)
			ft_printf(" ");
		current = current->next;
	}
	if (newline)
		ft_printf("\n");
}

void	ft_echo(t_token *tokens, int *exit_status, t_minishell *shell)
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
	*exit_status = 0;
	echo_print_tokens(current, exit_status, newline, shell);
}

void	ft_cd(t_token *tokens, char **env, int *exit_status)
{
	char	*path;
	int		ret;

	if (tokens->next == NULL)
	{
		path = ft_getenv("HOME", env);
	}
	else
	{
		if (tokens->next->next != NULL)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			*exit_status = 1;
			return ;
		}
		path = tokens->next->value;
	}
	if (!path)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		*exit_status = 1;
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, strlen(path));
		write(2, ": ", 2);
		write(2, strerror(errno), strlen(strerror(errno)));
		write(2, "\n", 1);
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
