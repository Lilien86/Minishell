/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/04/10 11:11:45 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	(void)shell;
	if (file->name != NULL)
	{
		if (is_append)
			file->fd = open(file->name, O_RDWR | O_APPEND);
		else
			file->fd = open(file->name, O_RDWR | O_TRUNC);
		if (file->fd == -1)
		{
			ft_printf("Error open file %s\n", file->name);
			return ;
		}
	}
}
/*
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
*/

int	init_redirect_array(t_minishell *shell)
{
	shell->nb_cmds = counter_cmds(shell->tokens);
	shell->redirect_array = calloc((size_t)shell->nb_cmds, sizeof(t_redirect));
	if (shell->redirect_array == NULL)
	{
		perror("Error malloc data_array");
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	fill_redirect_array(t_minishell *shell)
{
	t_token	*current;
	int		i;

	i = 0;
	current = shell->tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_REDIRECT_IN)
			handle_input_redirect(shell, current, &i);
		else if (current->type == TOKEN_REDIRECT_OUT)
			handle_output_redirect(shell, current, &i, 0);
		else if (current->type == TOKEN_DOUBLE_REDIRECT_OUT)
			handle_output_redirect(shell, current, &i, 1);
		else if (current->type == TOKEN_HEREDOC)
			handle_heredoc(shell, current, &i);
		else if (current->type == TOKEN_PIPE)
			handle_pipe(shell, &i);
		current = current->next;
	}
}

void	fill_t_redirect(t_minishell *shell)
{
	if (!init_redirect_array(shell))
		return ;
	fill_redirect_array(shell);
	print_data(shell->redirect_array, shell->nb_cmds);
}
