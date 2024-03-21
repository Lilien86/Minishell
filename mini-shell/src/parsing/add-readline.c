# include "../minishell.h"

#define MAX_HISTORY_SIZE 100

void	read_input_two(char *input, char *history[MAX_HISTORY_SIZE], int *history_index)
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

int	read_input(void)
{
	char	*input;
	char	*history[MAX_HISTORY_SIZE] = {NULL};
	int		history_index;

	history_index = 0;
	while (1)
	{
		input = readline("pipicaca > ");
		if (input == NULL)
			break;
		else if (strcmp(input, "") == 0)
			continue ;
		read_input_two(input, (history), &history_index);
		if (strcmp(input, "exit") == 0)
		{
			if (input)
				free(input);
			break ;
		}
		if (input)
			free(input);
	}
	free_history(history);
	return (0);
}