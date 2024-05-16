/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/05/16 08:52:25 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_file(t_file *file, int is_append, t_minishell *shell, int status)
{
	//(void)shell;
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

void	handle_input_output(t_minishell cpy, int *i, t_minishell *shell,
		int here_doc_available)
{
	if (cpy.tokens->type == TOKEN_HEREDOC && here_doc_available == 0)
	{
		to_choice_here_doc(&cpy, i);
		here_doc_available = 1;
	}
	if (cpy.tokens->type == TOKEN_REDIRECT_IN)
		handle_input_redirect(&cpy, cpy.tokens, i, shell);
	else if (cpy.tokens->type == TOKEN_REDIRECT_OUT)
		handle_output_redirect(&cpy, cpy.tokens, i, 0, shell);
	else if (cpy.tokens->type == TOKEN_DOUBLE_REDIRECT_OUT)
		handle_output_redirect(&cpy, cpy.tokens, i, 1, shell);
}

void	fill_redirect_array(t_minishell *shell)
{
	t_minishell	cpy;
	int			i;
	int			here_doc_available;

	shell->tab_here_doc = run_here_doc(shell);
	cpy = *shell;
	here_doc_available = 0;
	i = 0;
	while (cpy.tokens != NULL)
	{
		handle_input_output(cpy, &i, shell, here_doc_available);
		if (cpy.tokens->type == TOKEN_PIPE)
		{
			handle_pipe(&cpy, &i);
			here_doc_available = 0;
		}
		if (cpy.tokens->type == TOKEN_WORD
			&& (cpy.tokens->value != cpy.redirect_array[i].infile.name
				&& cpy.tokens->value != cpy.redirect_array[i].outfile.name))
			handle_word(&cpy, &cpy.tokens, &i);
		else
		{
			if (cpy.tokens->type != TOKEN_PIPE)
				cpy.tokens = cpy.tokens->next;
			cpy.tokens = cpy.tokens->next;
		}
	}
	free_tab_here_doc(shell->tab_here_doc, shell->nb_cmds);
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
