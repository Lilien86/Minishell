/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_s_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/04/05 11:53:06 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_data(t_data *data_array, int nb_cmds)
{
	int i;

	i = 0;
	while (i < nb_cmds)
	{
		ft_printf("Commande %d\n", i);
		ft_printf("Infile : %s\n", data_array[i].infile.name);
		ft_printf("Outfile : %s\n", data_array[i].outfile.name);
		ft_printf("Infile fd : %d\n", data_array[i].infile.fd);
		ft_printf("Outfile fd : %d\n", data_array[i].outfile.fd);
		i++;
	}
}

int	counter_cmds(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count + 1);
}

void	check_file(t_file *file, int is_append)
{
	if (file->name != NULL)
	{
		if (is_append)
			file->fd = open(file->name, O_RDWR | O_APPEND);
		else
			file->fd = open(file->name, O_RDWR | O_TRUNC);
		if (file->fd == -1)
		{
			ft_printf("Error open file %s\n", file->name);
			exit(EXIT_FAILURE);
		}
	}
}

void	fill_s_data(t_token tokens)
{
	int		nb_cmds;
	t_data	*data_array;
	t_token	*current;
	int		i;

	i = 0;
	nb_cmds = counter_cmds(&tokens);
	current = &tokens;
	data_array = ft_calloc((size_t)nb_cmds, sizeof(t_data));
	if (data_array == NULL)
	{
		perror("Error malloc data_array");
		exit(EXIT_FAILURE);
	}
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
		{
			i++;
		}
		else if (current->type == TOKEN_REDIRECT_IN)
		{
			data_array[i].infile.name = current->next->value;
			check_file(&data_array[i].infile, 0);
		}
		else if (current->type == TOKEN_REDIRECT_OUT)
		{
			data_array[i].outfile.name = current->next->value;
			check_file(&data_array[i].outfile, 0);
		}
		else if (current->type == TOKEN_DOUBLE_REDIRECT_OUT)
		{
			data_array[i].outfile.name = current->next->value;
			check_file(&data_array[i].outfile, 1);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			//here_doc(&tokens, &data_array[i]);
			here_doc(&tokens);
			check_file(&data_array[i].infile, 0);
		}
		current = current->next;
	}
	print_data(data_array, nb_cmds);
}

/* lilien tu vas devoir looper sur la linke list, quand tu rencontre un pipe tu passe a 
l'index suivant dans data_array et tu passe a l'element suivant dans la linked list doc apres le pipe.
quand tu rencontre un < c'est que l'infile est juste apres, et quand c'et un > le oufile est apres.
Oublie pas d'initailiser le infile et oufile a null comme ca tu sais si il existe, et check ussi avec open si tu peu les ouvrire*/