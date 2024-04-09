/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:43:37 by lauger            #+#    #+#             */
/*   Updated: 2024/04/09 10:59:11 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	handle_here_doc(t_minishell *shell, int i, char *delimiter)
{
	char		*line;
	char		*here_doc_content;
	char		*temp;
	size_t		len;

	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	here_doc_content = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
				"by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (here_doc_content == NULL)
			here_doc_content = ft_strdup(line);
		else
		{
			len = ft_strlen(here_doc_content) + ft_strlen(line) + 2;
			temp = ft_calloc(len, 1);
			ft_strcpy(temp, here_doc_content);
			ft_strcat(temp, "\n");
			ft_strcat(temp, line);
			free(here_doc_content);
			here_doc_content = temp;
		}
		free(line);
	}
	write_here_doc_in_file(here_doc_content,
		shell->redirect_array[i].infile.fd, shell);
	free_minishell(shell);
	exit(0);
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_and_process_line(char *delimiter, char *here_doc_content)
{
	char	*line;

	line = readline("> ");
	if (line == NULL)
	{
		ft_printf("\nbash: warning: here-document at line 1 delimited by"
			"end-of-file (wanted `%s')\n", delimiter);
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	if (here_doc_content == NULL)
		here_doc_content = ft_strdup(line);
	else
	{
		size_t len = ft_strlen(here_doc_content) + ft_strlen(line) + 2;
		char *temp = ft_calloc(len, 1);
		ft_strcpy(temp, here_doc_content);
		ft_strcat(temp, "\n");
		ft_strcat(temp, line);
		free(here_doc_content);
		here_doc_content = temp;
	}
	free(line);
	return (here_doc_content);
}

void handle_here_doc(t_minishell *shell, int i, char *delimiter)
{
	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	char *here_doc_content = NULL;
	while (1)
	{
		here_doc_content = read_and_process_line(delimiter, here_doc_content);
		if (here_doc_content == NULL) {
			break ;
		}
	}
	write_here_doc_in_file(here_doc_content, shell->redirect_array[i].infile.fd, shell);
	free_minishell(shell);
	exit(0);
}


