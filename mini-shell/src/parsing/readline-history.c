#include "../minishell.h"

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