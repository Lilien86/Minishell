#include "../minishell.h"
#define MAX_HISTORY_SIZE 100

void	read_input_two(char *input, char *history[MAX_HISTORY_SIZE],
			int *history_index)
{
	t_token	*tokens;
	t_token	*temp;

	if (strcmp(input, "") != 0)
	{
		add_history(input);
		if (history[*history_index] != NULL)
			free(history[*history_index]);
		history[*history_index] = strdup(input);
		*history_index = (*history_index + 1) % MAX_HISTORY_SIZE;
		tokens = tokenize(input);
		ft_printf("Tokens:\n");
		temp = tokens;
		while (temp)
		{
			ft_printf("Type: %d, Value: %s\n", temp->type, temp->value);
			temp = temp->next;
		}
	}
	free_tokens(&tokens);
	return ;
}

void	free_history(char *history[MAX_HISTORY_SIZE])
{
	int	i;

	i = 0;
	while (i < MAX_HISTORY_SIZE)
	{
		if (history[i] != NULL)
			free(history[i]);
		i++;
	}
}

void	init_history(char *history[MAX_HISTORY_SIZE])
{
	int	i;

	i = 0;
	while (i <= MAX_HISTORY_SIZE)
	{
		history[i] = NULL;
		i++;
	}
}

static void	handle_input(char *input, char *history[MAX_HISTORY_SIZE],
			int *history_index)
{
	if (strcmp(input, "") == 0)
		return ;
	add_history(input);
	if (history[*history_index] != NULL)
		free(history[*history_index]);
	history[*history_index] = strdup(input);
	*history_index = (*history_index + 1) % MAX_HISTORY_SIZE;
	read_input_two(input, history, history_index);
	if (strcmp(input, "exit") == 0)
	{
		free(input);
		exit(0);
	}
}

int	read_input(void)
{
	char	*input;
	char	*history[MAX_HISTORY_SIZE];
	int		history_index;

	history_index = 0;
	init_signal_handlers();
	init_history(history);
	while (1)
	{
		input = readline("Monsieur T-shirt > ");
		if (input == NULL)
		{
			free_history(history);
			exit(0);
		}
		handle_input(input, history, &history_index);
		free(input);
	}
	return (0);
}
