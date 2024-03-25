#include "../minishell.h"

t_token	*process_input(char *input, char *history[MAX_HISTORY_SIZE],
		int *history_index)
{
	t_token	*tokens;

	add_history(input);
	if (history[*history_index] != NULL)
		free(history[*history_index]);
	history[*history_index] = strdup(input);
	*history_index = (*history_index + 1) % MAX_HISTORY_SIZE;
	tokens = tokenize(input);
	execute_command(tokens);
	//free_tokens(&tokens);
	return (tokens);
}

void	execute_command(t_token *tokens)
{
	if (!tokens)
		return ;
	if (ft_strncmp(tokens->value, "echo", 4) == 0)
		ft_echo(tokens);
	else if (ft_strncmp(tokens->value, "cd", 2) == 0)
		ft_cd(tokens, environ);
	else if (ft_strncmp(tokens->value, "pwd", 3) == 0)
		ft_pwd();
}

t_token	*handle_input(char *input, char *history[MAX_HISTORY_SIZE],
	int *history_index)
{
	t_token	*tokens;

	if (strcmp(input, "") == 0)
		return ;
	tokens = process_input(input, history, history_index);
	if (strcmp(input, "exit") == 0)
	{
		free(input);
		exit(0);
	}
	return (tokens);
}

t_token	*read_input(void)
{
	char	*input;
	char	*history[MAX_HISTORY_SIZE];
	int		history_index;
	t_token	*tokens;

	history_index = 0;
	init_signal_handlers();
	init_history(history);
	while (1)
	{
		input = readline("minishell >");
		if (input == NULL)
		{
			free_history(history);
			exit(0);
		}
		tokens = handle_input(input, history, &history_index);
		syntax_analyse(tokens);
		free(input);
	}
	return (tokens);
}
