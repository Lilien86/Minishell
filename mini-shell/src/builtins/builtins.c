#include "../minishell.h"

void	echo_print_tokens(t_token *tokens, int *exit_status, int newline,
		t_minishell *shell)
{
	t_token	*current;

	(void)shell;
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
		if (current->next != NULL)
			ft_printf(" ");
		if (current->next == NULL)
			break ;
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
	current = tokens;
	if (current)
		current = current->next;
	while (current && is_flag_n(current->value))
	{
		newline = 0;
		current = current->next;
	}
	*exit_status = 0;
	echo_print_tokens(current, exit_status, newline, shell);
}

void	ft_pwd(t_token *arg_lst, int *exit_status)
{
	char	*cwd;

	if (arg_lst->next && arg_lst->next->value)
	{
		ft_printf("pwd: too many arguments\n");
		*exit_status = 127;
		return ;
	}
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
