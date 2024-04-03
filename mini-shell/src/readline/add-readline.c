#include "../minishell.h"

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		ft_printf("Type de Token: %d, Valeur: %s\n",
			current->type, current->value);
		current = current->next;
	}
}

void	process_input(t_minishell *shell)
{
    add_history(shell->input);
    if (shell->history[shell->history_index] != NULL)
        free(shell->history[shell->history_index]);
    shell->history[shell->history_index] = strdup(shell->input);
    shell->history_index = (shell->history_index + 1) % MAX_HISTORY_SIZE;
    shell->tokens = tokenize(shell->input);
    if (shell->tokens) 
        execute_command(shell);
    free_tokens(&(shell->tokens));
}

void execute_command(t_minishell *shell)
{
    if (!shell->tokens)
        return;
    if (ft_strncmp(shell->tokens->value, "echo", 4) == 0)
        ft_echo(shell->tokens);
    else if (ft_strncmp(shell->tokens->value, "cd", 2) == 0)
        ft_cd(shell->tokens, shell->env);
    else if (ft_strncmp(shell->tokens->value, "pwd", 3) == 0)
        ft_pwd();
    else if (ft_strncmp(shell->tokens->value, "export", 6) == 0)
        ft_export(shell->tokens, &(shell->env));
	else if (ft_strncmp(shell->tokens->value, "unset", 5) == 0)
		ft_unset(shell->tokens, &(shell->env));
}

void	handle_input(t_minishell *shell)
{
    if (strcmp(shell->input, "") == 0)
        return;
    process_input(shell);
    if (strcmp(shell->input, "exit") == 0)
	{
        free_minishell(shell);
        exit(0);
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
    }
    return (0);
}
