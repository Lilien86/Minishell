/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:10:09 by lauger            #+#    #+#             */
/*   Updated: 2024/06/14 12:19:09 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_file_names(t_minishell *shell, int index)
{
	if (shell->redirect_array[index].infile.name != NULL)
	{
		if (shell->redirect_array[index].infile.is_allocated == 1)
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

int	is_valid_fd(int fd)
{
	if (fd == -1 || fd == -2 || fd == 0 || fd == 1 || fd == 2)
		return (0);
	return (1);
}

void	free_redirect_array(t_minishell *shell, int size)
{
	int	i;

	if (shell->redirect_array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		if (shell->redirect_array[i].infile.name != NULL)
			free_file_names(shell, i);
		if (is_valid_fd(shell->redirect_array[i].infile.fd) == 1)
			close(shell->redirect_array[i].infile.fd);
		if (is_valid_fd(shell->redirect_array[i].outfile.fd) == 1)
			close(shell->redirect_array[i].outfile.fd);
		if (shell->redirect_array[i].argv != NULL)
			free_arguments(shell, i);
		i++;
	}
	free(shell->redirect_array);
	shell->redirect_array = NULL;
}
