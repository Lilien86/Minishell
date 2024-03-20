/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add-readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:16:29 by lauger            #+#    #+#             */
/*   Updated: 2024/03/20 11:11:49 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

#define MAX_HISTORY_SIZE 100

void	read_input_two(char *input, char *history[MAX_HISTORY_SIZE], int *history_index)
{
	if (strcmp(input, "") != 0)
	{
		add_history(input);
		if (history[*history_index] != NULL)
			free(history[*history_index]);
		history[*history_index] = strdup(input);
		*history_index = (*history_index + 1) % MAX_HISTORY_SIZE;
		tokenize(input);
		
	}
	return ;
}

int	read_input(void)
{
	char	*input;
	char	*history[MAX_HISTORY_SIZE] = {NULL};
	int		history_index;
	int		i;

	history_index = 0;
	i = 0;
	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL || strcmp(input, "") == 0)
		{
			break ;
		}
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
	while (i < MAX_HISTORY_SIZE)
	{
		if (history[i] != NULL)
			free(history[i]);
		i++;
	}
	return (0);
}
