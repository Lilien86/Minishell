#include "../minishell.h"

/**
 * @brief Frees the memory allocated for the history array.
 * 
 * This function iterates over the history array and frees the memory allocated for each element.
 * 
 * @param history The history array to be freed.
 */
void free_history(char *history[MAX_HISTORY_SIZE])
{
	int i;

	i = 0;
	while (i < MAX_HISTORY_SIZE)
	{
		if (history[i] != NULL)
			free(history[i]);
		i++;
	}
}

/**
 * @brief Initializes the history array.
 * 
 * This function initializes the history array by setting all elements to NULL.
 * 
 * @param history The history array to be initialized.
 */
void init_history(char *history[MAX_HISTORY_SIZE])
{
	int i;

	i = 0;
	while (i <= MAX_HISTORY_SIZE)
	{
		history[i] = NULL;
		i++;
	}
}
