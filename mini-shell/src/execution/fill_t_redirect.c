/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/05/10 09:06:02 by lauger           ###   ########.fr       */
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

void	check_file(t_file *file, int is_append, t_minishell *shell, int status)
{
	(void)shell;
	if (file->name != NULL)
	{
		if (is_append)
			file->fd = open(file->name, O_WRONLY | O_APPEND);
		else if (status == 1)
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (status == 0)
			file->fd = open(file->name, O_RDONLY, 0644);
		if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0)
		{
			ft_printf("minishell: %s: ", file->name);
			perror(NULL);
			shell->exit_status = 1;
			shell->redirect_array[0].infile.fd = -2;
			return ;
		}
	}
}

int	init_redirect_array(t_minishell *shell)
{
	shell->nb_cmds = counter_cmds(shell->tokens);
	shell->redirect_array = ft_calloc((size_t)shell->nb_cmds,
			sizeof(t_redirect));
	if (shell->redirect_array == NULL)
	{
		perror("Error malloc data_array");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	remplace_here_doc(t_minishell *shell, int *i)
{
	int		j;
	t_token	*current;

	j = -1;
	current = shell->tokens;
	if (*i != 0)
	{
		while (*i != j)
		{
			while (current->type != TOKEN_PIPE && current != NULL)
				current = current->next;
			j++;
		}
	}
	while (current->type != TOKEN_HEREDOC && current != NULL)
		current = current->next;
	
}

int	counter_here_doc(t_token *tokens)
{
	int	count;
	int	i;
	
	count = 0;
	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_HEREDOC)
			count++;
		if (tokens->type == TOKEN_PIPE)
			break;
		tokens = tokens->next;
	}
	return (count);
}

void	run_here_doc(t_minishell *shell)
{
	t_token	*current;
	t_file 	**tab_here_doc;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current = shell->tokens;
	tab_here_doc = ft_calloc(((size_t)shell->nb_cmds), sizeof(t_file *));
	if (tab_here_doc == NULL)
		error_exit("Error malloc here_doc", shell);
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (j == 0)
			{
				tab_here_doc[i] = ft_calloc((size_t)counter_here_doc(current), sizeof(t_file));
				if (tab_here_doc[i] == NULL)
					error_exit("Error malloc here_doc", shell);
			}
			tab_here_doc[i][j] = here_doc_2(current, shell);
			j++;
		}
		else if (current->type == TOKEN_PIPE)
		{
			i++;
			j = 0;
		}
		current = current->next;
	}
	shell->tab_here_doc = tab_here_doc;
}


void	to_choice_here_doc(t_minishell *shell, int *i)
{
	int		j;
	int		nb_here_doc;

	j = 0;
	nb_here_doc = counter_here_doc(shell->tokens);
	while (nb_here_doc != 0 && j != *i)
	{
		close(shell->tab_here_doc[*i][j].fd);
		j++;
	}
	if (shell->tab_here_doc && nb_here_doc != 0)
	{
		close (shell->tab_here_doc[*i][nb_here_doc - 1].fd);
		shell->redirect_array[*i].infile.fd = open (shell->tab_here_doc[*i][nb_here_doc - 1].name, O_RDONLY);
		if (shell->tab_here_doc[*i][nb_here_doc - 1].fd == -1)
			error_exit("Error open here_doc", shell);
		shell->redirect_array[*i].infile.name = shell->tab_here_doc[*i][nb_here_doc - 1].name;
	}

}

void	fill_redirect_array(t_minishell *shell)
{
	t_minishell	cpy;
	int			i;
	int			here_doc_available;

	run_here_doc(shell);
	cpy = *shell;
	here_doc_available = 0;
	i = 0;
	while (cpy.tokens != NULL)
	{
		if (cpy.tokens->type == TOKEN_HEREDOC && here_doc_available == 0)
		{ 
			to_choice_here_doc(&cpy, &i);
			here_doc_available = 1;
		}
		if (cpy.tokens->type == TOKEN_REDIRECT_IN)
			handle_input_redirect(&cpy, cpy.tokens, &i, shell);
		else if (cpy.tokens->type == TOKEN_REDIRECT_OUT)
			handle_output_redirect(&cpy, cpy.tokens, &i, 0, shell);
		else if (cpy.tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
			handle_output_redirect(&cpy, cpy.tokens, &i, 1, shell);
		else if (cpy.tokens->type == TOKEN_PIPE)
		{
			handle_pipe(&cpy, &i);
			here_doc_available = 0;
		}	
		if (cpy.tokens->type == TOKEN_WORD
			&& (cpy.tokens->value != cpy.redirect_array[i].infile.name
				&& cpy.tokens->value != cpy.redirect_array[i].outfile.name))
			handle_word(&cpy, &cpy.tokens, &i);
		else {
			if (cpy.tokens->type != TOKEN_PIPE)
				cpy.tokens = cpy.tokens->next;
			cpy.tokens = cpy.tokens->next;
		}
	}
}

void	fill_t_redirect(t_minishell *shell)
{
	if (!init_redirect_array(shell))
		return ;
	shell->redirect_array[0].infile.name = NULL;
	shell->redirect_array[0].infile.fd = -1;
	shell->redirect_array[0].outfile.name = NULL;
	shell->redirect_array[0].outfile.fd = -1;
	shell->redirect_array[0].argv = NULL;
	shell->exit_status = 0;
	fill_redirect_array(shell);
	//print_data(shell->redirect_array, shell->nb_cmds);
}
