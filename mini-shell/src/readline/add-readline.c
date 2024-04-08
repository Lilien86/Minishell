#include "../minishell.h"

// void	debug_print_tokens(t_token *tokens)
// {
// 	t_token	*current;

// 	current = tokens;
// 	while (current != NULL)
// 	{
// 		ft_printf("Type de Token: %d, Valeur: %s\n",
// 			current->type, current->value);
// 		current = current->next;
// 	}
// }

void	process_input(t_minishell *shell)
{
	add_history(shell->input);
	if (shell->history[shell->history_index] != NULL)
		free(shell->history[shell->history_index]);
	shell->history[shell->history_index] = ft_strdup(shell->input);
	shell->history_index = (shell->history_index + 1) % MAX_HISTORY_SIZE;
	shell->tokens = tokenize(shell->input);
	if (shell->tokens)
	{
		execute_command(shell);
		fill_s_data(shell);
	}
}

void	execute_command(t_minishell *shell)
{
	if (!shell->tokens)
		return ;
	if (ft_strncmp(shell->tokens->value, "echo", 4) == 0)
		ft_echo(shell->tokens, &shell->exit_status);
	else if (ft_strncmp(shell->tokens->value, "cd", 2) == 0)
		ft_cd(shell->tokens, shell->env, &shell->exit_status);
	else if (ft_strncmp(shell->tokens->value, "pwd", 3) == 0)
		ft_pwd(&shell->exit_status);
	else if (ft_strncmp(shell->tokens->value, "export", 6) == 0)
		ft_export(shell->tokens, &(shell->env), &shell->exit_status);
	else if (ft_strncmp(shell->tokens->value, "unset", 5) == 0)
		ft_unset(shell->tokens, &shell->env, &shell->exit_status);
	else if (ft_strncmp(shell->tokens->value, "env", 3) == 0
		&& shell->tokens->value[3] == '\0')
		ft_env(shell->env, &shell->exit_status);
}

void	handle_input(t_minishell *shell)
{
	if (ft_strcmp(shell->input, "") == 0)
		return ;
	if (ft_strcmp(shell->input, "$?") == 0)
		ft_printf("%d\n", shell->exit_status);
	process_input(shell);
	if (ft_strcmp(shell->input, "exit") == 0)
	{
		free_minishell(shell);
		exit(shell->exit_status);
	}
}

int	read_input(t_minishell *shell)
{
	while (1)
	{
		shell->input = readline("minishell > ");
		if (shell->input == NULL)
		{
			free_minishell(shell);
			exit(0);
		}
		handle_input(shell);
		free(shell->input);
		free_tokens(&(shell->tokens));
	}
	return (0);
}
