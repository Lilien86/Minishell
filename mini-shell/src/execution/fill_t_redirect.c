/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/04/15 13:31:56 by lauger           ###   ########.fr       */
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

int	init_redirect_array(t_minishell *shell)
{
	shell->nb_cmds = counter_cmds(shell->tokens);
	shell->redirect_array = ft_calloc((size_t)shell->nb_cmds, sizeof(t_redirect));
	if (shell->redirect_array == NULL)
	{
		perror("Error malloc data_array");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	return (1);
}

/*void	fill_redirect_array(t_minishell *shell)
{
	int			i;

	i = 0;
	if (shell->tokens == NULL)
		return ;
	while (shell->tokens != NULL)
	{
		if (shell->tokens->type == TOKEN_REDIRECT_IN)
			handle_input_redirect(shell, shell->tokens, &i);
		else if (shell->tokens->type == TOKEN_REDIRECT_OUT)
			handle_output_redirect(shell, shell->tokens, &i, 0);
		else if (shell->tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
			handle_output_redirect(shell, shell->tokens, &i, 1);
		else if (shell->tokens->type == TOKEN_HEREDOC)
			handle_heredoc(shell, shell->tokens, &i);
		else if (shell->tokens->type == TOKEN_PIPE)
			handle_pipe(shell, &i);
		if (1)
		{
			if (shell->tokens->type == TOKEN_WORD && (shell->tokens->value != shell->redirect_array[i].infile.name && shell->tokens->value != shell->redirect_array[i].outfile.name))
				handle_word(shell, &shell->tokens, &i);
			else
				shell->tokens = shell->tokens->next;
		}
	}
}*/

void fill_redirect_array(t_minishell *shell)
{
	t_minishell	cpy;
	int			i;

	i = 0;
	cpy = *shell;
	if (cpy.tokens == NULL)
		return;
	while (cpy.tokens != NULL)
	{
		if (cpy.tokens->type == TOKEN_REDIRECT_IN)
			handle_input_redirect(&cpy, cpy.tokens, &i);
		else if (cpy.tokens->type == TOKEN_REDIRECT_OUT)
			handle_output_redirect(&cpy, cpy.tokens, &i, 0);
		else if (cpy.tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
			handle_output_redirect(&cpy, cpy.tokens, &i, 1);
		else if (cpy.tokens->type == TOKEN_HEREDOC)
			handle_heredoc(&cpy, cpy.tokens, &i);
		else if (cpy.tokens->type == TOKEN_PIPE)
			handle_pipe(&cpy, &i);
		if (1)
		{
			/*if ((cpy.redirect_array[i].infile.name != NULL || cpy.redirect_array[i].outfile.name != NULL) && cpy.tokens->type == TOKEN_WORD)
			{
				ft_printf("Error: redirection file must be the last token\n");
				free_minishell(shell);
				exit(EXIT_FAILURE);
			}*/
			if (cpy.tokens->type == TOKEN_WORD && (cpy.tokens->value != cpy.redirect_array[i].infile.name && cpy.tokens->value != cpy.redirect_array[i].outfile.name))
				handle_word(&cpy, &cpy.tokens, &i);
			else
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
	print_data(shell->redirect_array, shell->nb_cmds);
}
