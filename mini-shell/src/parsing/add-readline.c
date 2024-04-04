#include "../minishell.h"

/**
 * @brief Prints the type and value of each token in a linked list.
 * 
 * @param tokens The linked list of tokens.
 */
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

/**
 * @brief Processes the user input by adding it to the history
 * tokenizing it, and executing the command.
 * 
 * @param input The user input string.
 * @param history The array of previous input history.
 * @param history_index The index of the current input in the history array.
 */
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

/**
 * @brief Executes the command based on the tokens.
 * 
 * @param tokens The linked list of tokens representing the command.
 */
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
	else if (ft_strncmp(tokens->value, "export", 6) == 0)
		ft_export(tokens, &environ);
}

/**
 * @brief Handles the user input by processing it and checking
 * for the "exit" command.
 * 
 * @param input The user input string.
 * @param history The array of previous input history.
 * @param history_index The index of the current input in the history array.
 */
t_token	*handle_input(char *input, char *history[MAX_HISTORY_SIZE],
					int *history_index)
{
	t_token *tokens;

	if (strcmp(input, "") == 0)
		return (NULL);
	tokens = process_input(input, history, history_index);
	process_input(input, history, history_index);
	if (strcmp(input, "exit") == 0)
	{
		free(input);
		free_history(history);
		free_tokens(&tokens);
		exit(0);
	}
	return (tokens);
}

/**
 * @brief Reads user input, adds it to history, and handles
 * the input by calling the appropriate functions.
 * 
 * @return 0 on success.
 */
void	read_input(void)
{
	char *input;
	char *history[MAX_HISTORY_SIZE];
	int history_index;
	t_token	*tokens;

	history_index = 0;
	init_signal_handlers();
	init_history(history);
	while (1)
	{
		input = readline("minishell > ");
		//debug_print_tokens(tokenize(input));
		if (input == NULL)
		{
			free_history(history);
			//free_tokens(&tokens);
			ft_printf("proute\n");
			exit(0);
		}
		tokens = handle_input(input, history, &history_index);
		here_doc(tokens);
		free(input);
		//free_tokens(&tokens);
	}
	//free_tokens(&tokens);
}
