/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:44:00 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/18 11:47:56 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_and_process_line(char *delimiter)
{
	char	*line;

	line = read_line(delimiter);
	if (line == NULL)
		return (NULL);
	delimiter = ft_strjoin(line, "\n");
	return (delimiter);
}

void	init_signals(void)
{
	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
}

void	read_here_doc(t_minishell *shell, t_file here_doc, char *delimiter,
	char **here_doc_content)
{
	char	*temp;
	char	*temp2;

	(void)here_doc;
	while (1)
	{
		temp = read_and_process_line(delimiter);
		if (temp == NULL)
		{
			shell->exit_status = 2;
			break ;
		}
		temp2 = *here_doc_content;
		*here_doc_content = ft_strjoin(*here_doc_content, temp);
		free(temp2);
		free(temp);
	}
}

void	write_here_doc(t_minishell *shell, t_file here_doc,
	char *here_doc_content, int replace_env)
{
	char	*here_doc_content_env;

	here_doc_content_env = NULL;
	if (replace_env != 0)
	{
		here_doc_content_env = (char *)here_doc_replace_var_env(
				here_doc_content, shell);
		write_here_doc_in_file(here_doc_content_env, here_doc.fd, shell);
	}
	else
	{
		write_here_doc_in_file(here_doc_content, here_doc.fd, shell);
	}
	free_minishell(shell);
	free(here_doc.name);
	close(here_doc.fd);
	free(here_doc_content);
	free(here_doc_content_env);
	exit(EXIT_SUCCESS);
}

void	handle_here_doc(t_minishell *shell, t_file here_doc,
		char *delimiter, int replace_env)
{
	char	*here_doc_content;

	here_doc_content = NULL;
	remember_fd_here_doc(&here_doc, shell);
	init_signals();
	read_here_doc(shell, here_doc, delimiter, &here_doc_content);
	write_here_doc(shell, here_doc, here_doc_content, replace_env);
}
