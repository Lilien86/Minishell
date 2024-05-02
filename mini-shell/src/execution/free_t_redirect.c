/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:10:09 by lauger            #+#    #+#             */
/*   Updated: 2024/05/02 11:24:30 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void free_redirect_array(t_minishell *shell, int size)
{
	int i = 0;
	if (shell->redirect_array == NULL)
		return;
	while (i < (size))
	{
		if (shell->redirect_array)
		{
			if (shell->redirect_array[i].infile.name != NULL)
			{
				free(shell->redirect_array[i].infile.name);
				shell->redirect_array[i].infile.name = NULL;
			}
			if (shell->redirect_array[i].outfile.name)
			{
				//free(shell->redirect_array[i].outfile.name);
				shell->redirect_array[i].outfile.name = NULL;
			}
			if (shell->redirect_array[i].argv != NULL)
			{
				int j = 0;
				while (shell->redirect_array[i].argv[j] != NULL)
				{
					free(shell->redirect_array[i].argv[j]);
					shell->redirect_array[i].argv[j] = NULL;
					j++;
				}
				free(shell->redirect_array[i].argv);
				shell->redirect_array[i].argv = NULL;
			}
		}
		i++;
	}
	free(shell->redirect_array);
}*/

void	free_file_names(t_minishell *shell, int index)
{
	if (shell->redirect_array[index].infile.name != NULL)
	{
		free(shell->redirect_array[index].infile.name);
		shell->redirect_array[index].infile.name = NULL;
	}
	if (shell->redirect_array[index].outfile.name != NULL)
		shell->redirect_array[index].outfile.name = NULL;
}

void	free_arguments(t_minishell *shell, int index)
{
	int	j;

	j = 0;
	if (shell->redirect_array[index].argv != NULL)
	{
		while (shell->redirect_array[index].argv[j] != NULL)
		{
			free(shell->redirect_array[index].argv[j]);
			shell->redirect_array[index].argv[j] = NULL;
			j++;
		}
		free(shell->redirect_array[index].argv);
		shell->redirect_array[index].argv = NULL;
	}
}

void	free_redirect_array(t_minishell *shell, int size)
{
	int	i;

	if (shell->redirect_array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free_file_names(shell, i);
		free_arguments(shell, i);
		i++;
	}
	free(shell->redirect_array);
	shell->redirect_array = NULL;
}
