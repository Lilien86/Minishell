/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:10:09 by lauger            #+#    #+#             */
/*   Updated: 2024/04/09 12:36:46 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_redirect_array(t_redirect **redirect_array, int size)
{
	int i = 0;
	if (redirect_array == NULL)
		return;
	while (i < size)
	{
		if (redirect_array[i] != NULL)
		{
			if (redirect_array[i]->infile.name != NULL)
			{
				free(redirect_array[i]->infile.name);
				redirect_array[i]->infile.name = NULL;
			}
			if (redirect_array[i]->outfile.name != NULL)
			{
				free(redirect_array[i]->outfile.name);
				redirect_array[i]->outfile.name = NULL;
			}
			if (redirect_array[i]->argv != NULL)
			{
				int j = 0;
				while (redirect_array[i]->argv[j] != NULL)
				{
					free(redirect_array[i]->argv[j]);
					redirect_array[i]->argv[j] = NULL;
					j++;
				}
				free(redirect_array[i]->argv);
				redirect_array[i]->argv = NULL;
			}
			free(redirect_array[i]);
			redirect_array[i] = NULL;
		}
		i++;
	}
	free(redirect_array);
}

/*void	free_file_name(char **file_name)
{
	if (file_name != NULL && *file_name != NULL)
	{
		free(*file_name);
		*file_name = NULL;
	}
}*/

/*void	free_argv(char ***argv)
{
	if (argv != NULL && *argv != NULL)
	{
		int	j;

		j = 0;
		while ((*argv)[j] != NULL)
		{
			free((*argv)[j]);
			(*argv)[j] = NULL;
			j++;
		}
		free(*argv);
		*argv = NULL;
	}
}

void	free_redirect_element(t_redirect *redirect)
{
	if (redirect != NULL)
	{
		if (redirect->infile.name != NULL)
		{
			free(redirect->infile.name);
			redirect->infile.name = NULL;
		}
		if (redirect->outfile.name != NULL)
		{
			free(redirect->outfile.name);
			redirect->outfile.name = NULL;
		}
		//free_file_name(&(redirect->infile.name));
		//free_file_name(&(redirect->outfile.name));
		free_argv(&(redirect->argv));
		free(redirect);
		redirect = NULL;
	}
}

void	free_redirect_array(t_redirect **redirect_array, int size)
{
	int	i;

	if (redirect_array == NULL | size == 0)
		return ;
	i = 0;
	while (i < size)
	{
		free_redirect_element(redirect_array[i]);
		i++;
	}
}*/
