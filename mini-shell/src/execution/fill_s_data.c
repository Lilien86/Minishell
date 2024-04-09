/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_s_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/04/09 14:09:19 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_data(t_redirect *data_array, int nb_cmds)
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

void	check_file(t_file *file, int is_append, t_minishell *shell)
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
			free_minishell(shell);
			exit(EXIT_FAILURE);
		}
	}
}

void	fill_s_data(t_minishell *shell)
{
	t_token			*current;
	int				i;

	i = 0;
	shell->nb_cmds = counter_cmds(shell->tokens);
	current = shell->tokens;
	shell->redirect_array = ft_calloc((size_t)shell->nb_cmds, sizeof(t_redirect));
	if (shell->redirect_array == NULL)
	{
		perror("Error malloc data_array");
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
	shell->redirect_array[i].infile.name = NULL;
	shell->redirect_array[i].outfile.name = NULL;
	shell->redirect_array[i].argv = NULL;
	while (current != NULL)
	{
		
		if (current->type == TOKEN_REDIRECT_IN)
		{
			shell->redirect_array[i].infile.name = current->next->value;
			check_file(&shell->redirect_array[i].infile, 0, shell);
		}
		else if (current->type == TOKEN_REDIRECT_OUT)
		{
			shell->redirect_array[i].outfile.name = current->next->value;
			check_file(&shell->redirect_array[i].outfile, 0, shell);
		}
		else if (current->type == TOKEN_DOUBLE_REDIRECT_OUT)
		{
			shell->redirect_array[i].outfile.name = current->next->value;
			check_file(&shell->redirect_array[i].outfile, 1, shell);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			here_doc(current, shell, i);
		}
		else if (current->type == TOKEN_PIPE)
		{
			i++;
			shell->redirect_array[i].infile.name = NULL;
			shell->redirect_array[i].outfile.name = NULL;
			shell->redirect_array[i].argv = NULL;
		}
		current = current->next;
	}
	print_data(shell->redirect_array, shell->nb_cmds);
}

