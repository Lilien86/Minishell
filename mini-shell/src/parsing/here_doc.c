/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/04/03 08:24:43 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		handle_sigint_here_doc(int sig);
static void	fork_here_doc(char *delimiter);
static void handle_here_doc(char *delimiter);
static void	write_here_doc_in_file(char *content);

static void handle_here_doc(char *delimiter)
{
	char *line;
	char *here_doc_content = NULL;

	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
					  "by end-of-file (wanted `%s')\n",
					  delimiter);
			break;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (here_doc_content == NULL)
			here_doc_content = strdup(line);
		else
		{
			char *temp = malloc(strlen(here_doc_content) + strlen(line) + 2);
			sprintf(temp, "%s\n%s", here_doc_content, line);
			free(here_doc_content);
			here_doc_content = temp;
		}
		free(line);
	}
	//printf("\nContenu du here_doc :\n%s\n", here_doc_content);
	write_here_doc_in_file(here_doc_content);
	free(here_doc_content);
	exit(0);
}

static void	write_here_doc_in_file(char *content)
{
	int		fd;
	char	*filename;
	char	*full_path;

	filename = strdup(generate_random_filename());
	full_path = malloc(strlen("/tmp/") + strlen(filename) + 1);
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
}

static void	fork_here_doc(char *delimiter)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(delimiter);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		//ft_printf("The child process has finished\n");
	}
	else
	{
		perror("Error:\nduring fork_here_doc");
		exit(EXIT_FAILURE);
	}
}

static void	handle_sigint_here_doc(int sig)
{
	(void)sig;
	exit(0);
}

void	here_doc(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			//handle_here_doc(current->value);
			fork_here_doc(current->value);
		}
		current = current->next;
	}
}