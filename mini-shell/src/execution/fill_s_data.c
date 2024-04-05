/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_s_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/04/05 14:57:22 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_data(t_data *data_array, int nb_cmds)
{
	int i;

	i = 0;
	while (i < nb_cmds)
	{
		//ft_printf("Commande %d\n", i);
		ft_printf("Infile : %s\n", data_array[i].infile.name);
		ft_printf("Outfile : %s\n", data_array[i].outfile.name);
		ft_printf("Infile fd : %d\n", data_array[i].infile.fd);
		ft_printf("Outfile fd : %d\n", data_array[i].outfile.fd);
		ft_printf("-------\n\n");
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

/*void	handle_while_d_data(t_token **current, t_data **data_array, int i)
{
	if ((*current)->type == TOKEN_PIPE)
	{
		i++;
		*current = (*current)->next;
	}
	else if ((*current)->type == TOKEN_REDIRECT_IN)
	{
		(*data_array)[i].infile.name = (*current)->next->value;
		check_file(&(*data_array)[i].infile, 0);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == TOKEN_REDIRECT_OUT)
	{
		(*data_array)[i].outfile.name = (*current)->next->value;
		check_file(&(*data_array)[i].outfile, 0);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == TOKEN_DOUBLE_REDIRECT_OUT)
	{
		(*data_array)[i].outfile.name = (*current)->next->value;
		check_file(&(*data_array)[i].outfile, 1);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == TOKEN_HEREDOC)
	{
		here_doc(*current, data_array, i);
		check_file(&(*data_array)[i].infile, 0);
	}
}*/

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
			here_doc(current, &data_array, i);
			check_file(&data_array[i].infile, 0);
		}
		//handle_while_d_data(&current, &data_array, i);
		current = current->next;
	}
	print_data(data_array, nb_cmds);
}

