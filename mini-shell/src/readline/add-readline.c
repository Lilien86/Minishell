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

void	process_input(char *input, t_minishell *shell)
{
	t_token	*tokens;

	add_history(input);
	if (history[*history_index] != NULL)
		free(history[*history_index]);
	history[*history_index] = strdup(input);
	*history_index = (*history_index + 1) % MAX_HISTORY_SIZE;
	tokens = tokenize(input);
	execute_command(tokens, env);
	free_tokens(&tokens);
}

void	execute_command(t_token *tokens, char ***env)
{
	if (!tokens)
		return ;
	if (ft_strncmp(tokens->value, "echo", 4) == 0)
		ft_echo(tokens);
	else if (ft_strncmp(tokens->value, "cd", 2) == 0)
		ft_cd(tokens, *env);
	else if (ft_strncmp(tokens->value, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(tokens->value, "export", 6) == 0)
		ft_export(tokens, env);
}

void	handle_input(char *input, t_minishell *shell)
{
    if (strcmp(input, "") == 0)
        return;
    process_input(input, shell);
    if (strcmp(input, "exit") == 0)
	{
        free(input);
        free_minishell(shell);
        exit(0);
    }
}


int	read_input(t_minishell *shell)
{
    char	*input;

    while (1)
	{
        input = readline("minishell > ");
        if (input == NULL) {
            free_minishell(shell);
            exit(0);
        }
        handle_input(input, shell);
        free(input);
    }
    return (0);
}
