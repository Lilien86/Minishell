/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/04/05 08:35:41 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_here_doc_in_file(char *content)
{
	int		fd;
	char	*filename;
	char	*full_path;

	filename = generate_random_filename();
	full_path = ft_calloc(sizeof(char), (strlen(filename)
				+ strlen("/tmp/") + 1));
	if (full_path == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		return ;
	}
	full_path = ft_strncpy(full_path, "/tmp/", ft_strlen("/tmp/"));
	full_path = ft_strcat(full_path, filename);
	fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error:\nduring write_here_doc_in_file");
		exit(EXIT_FAILURE);
	}
	write(fd, content, strlen(content));
	free(full_path);
	free(filename);
}

void	handle_while_here_doc(char *delimiter, char *line,
	char *here_doc_content, char *temp)
{
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
				"by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (here_doc_content == NULL)
			here_doc_content = strdup(line);
		else
		{
			temp = malloc(strlen(here_doc_content) + strlen(line) + 2);
			sprintf(temp, "%s\n%s", here_doc_content, line);
			free(here_doc_content);
			here_doc_content = temp;
		}
		free(line);
	}
}

static void	handle_here_doc(char *delimiter, t_token **tokens)
{
	char	*line;
	char	*here_doc_content;
	char	*temp;

	here_doc_content = NULL;
	line = NULL;
	temp = NULL;
	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	handle_while_here_doc(delimiter, line, here_doc_content, temp);
	write_here_doc_in_file(here_doc_content);
	free(here_doc_content);
	free_tokens(tokens);
	exit(0);
}

static void	fork_here_doc(char *delimiter, t_token **tokens)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(delimiter, tokens);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("Error:\nduring fork_here_doc");
		exit(EXIT_FAILURE);
	}
}

void	here_doc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			fork_here_doc(current->value, &tokens);
		}
		current = current->next;
	}
}
