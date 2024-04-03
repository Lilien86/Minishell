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

void	process_input(char *input, char *history[MAX_HISTORY_SIZE],
					int *history_index, char ***env)
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

void	handle_input(char *input, char *history[MAX_HISTORY_SIZE],
					int *history_index, char ***env)
{
	if (strcmp(input, "") == 0)
		return ;
	process_input(input, history, history_index, env);
	if (strcmp(input, "exit") == 0)
	{
		free(input);
		exit(0);
	}
}

int	read_input(char ***env)
{
	char	*input;
	char	*history[MAX_HISTORY_SIZE];
	int		history_index;

	history_index = 0;
	init_signal_handlers();
	init_history(history);
	while (1)
	{
		input = readline("minishell >");
		//debug_print_tokens(tokenize(input));
		if (input == NULL)
		{
			free_history(history);
			exit(0);
		}
		handle_input(input, history, &history_index, env);
		free(input);
	}
	return (0);
}
