/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/04/05 14:57:57 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_here_doc_in_file(char *content, int fd, char *fullpath)
{
	ft_printf("\n+++++namefile : %s\n", fullpath);
	ft_printf("+++++fd : %d\n\n", fd);
	write(fd, content, strlen(content));
	free(fullpath);
}

static void handle_here_doc(t_token **tokens, t_data **data_array, int i, char *delimiter)
{
	char		*line;
	char		*here_doc_content = NULL;
	char		*temp;
	size_t		len;

	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
					"by end-of-file (wanted `%s')\n", delimiter);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
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
	//ft_printf("\nContenu du here_doc :\n%s\n", here_doc_content);
	write_here_doc_in_file(here_doc_content, data_array[i]->infile.fd, data_array[i]->infile.name);
	free(here_doc_content);
	free_tokens(tokens);
	exit(0);
}

static void	creat_file_descriptor(t_data **data_array, int i)
{
	char	*filename;

	filename = generate_random_filename();
	data_array[i]->infile.name = ft_calloc(sizeof(char) , (strlen(filename) + strlen("/tmp/") + 1));
	if (data_array[i]->infile.name == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		return ;
	}
	data_array[i]->infile.name = ft_strncpy(data_array[i]->infile.name, "/tmp/", ft_strlen("/tmp/"));
	data_array[i]->infile.name = ft_strcat(data_array[i]->infile.name, filename);
	data_array[i]->infile.fd = open(data_array[i]->infile.name, O_RDONLY);
	if (data_array[i]->infile.fd == -1)
	{
		perror("Error:\nduring creat_file_descriptor");
		exit(EXIT_FAILURE);
	}
}

void	fork_here_doc(char *delimiter, t_token **tokens, t_data **data_array, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	creat_file_descriptor(data_array, i);
	if (pid == 0)
	{
		handle_here_doc(tokens, data_array, i, delimiter);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("Error:\nduring fork_here_doc");
		exit(EXIT_FAILURE);
	}
}

void	here_doc(t_token *tokens, t_data **redirect, int i)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			fork_here_doc(current->value, &tokens, redirect, i);
			printf("name: %s\n", redirect[i]->infile.name);
			printf("fd: %d\n\n", redirect[i]->infile.fd);
		}
		current = current->next;
	}
}

/*static void	write_here_doc_in_file(char *content, t_data **data, int i)
{
	char	*filename;

	filename = generate_random_filename();
	data[i]->infile.name = ft_calloc(sizeof(char) , (strlen(filename) + strlen("/tmp/") + 1));
	if (data[i]->infile.name == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		return ;
	}
	data[i]->infile.name = ft_strncpy(data[i]->infile.name, "/tmp/", ft_strlen("/tmp/"));
	data[i]->infile.name = ft_strcat(data[i]->infile.name, filename);
	data[i]->infile.fd = open(data[i]->infile.name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data[i]->infile.fd == -1)
	{
		perror("Error:\nduring write_here_doc_in_file");
		exit(EXIT_FAILURE);
	}
	ft_printf("\n+++++namefile : %s\n", data[i]->infile.name);
	ft_printf("+++++fd : %d\n\n", data[i]->infile.fd);
	write(data[i]->infile.fd, content, strlen(content));
	// free(data[i]->infile.name);
	free(filename);
}

static void handle_here_doc(char *delimiter, t_token **tokens,
	t_data **data_array, int i)
{
	char		*line;
	char		*here_doc_content = NULL;
	char		*temp;
	size_t		len;

	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
					"by end-of-file (wanted `%s')\n", delimiter);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
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
	//ft_printf("\nContenu du here_doc :\n%s\n", here_doc_content);
	write_here_doc_in_file(here_doc_content, data_array, i);
	free(here_doc_content);
	free_tokens(tokens);
	exit(0);
}

void	creat_file_descriptor(t_data **data_array, int i)
{
	char	*filename;

	filename = generate_random_filename();
	data_array[i]->infile.name = ft_calloc(sizeof(char) , (strlen(filename) + strlen("/tmp/") + 1));
	if (data_array[i]->infile.name == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		return ;
	data_array[i]->infile.name = ft_strncpy(data_array[i]->infile.name, "/tmp/", ft_strlen("/tmp/"));
	data_array[i]->infile.name = ft_strcat(data_array[i]->infile.name, filename);
	data_array[i]->infile.fd = open(data_array[i]->infile.name, O_RDONLY);
	if (data_array[i]->infile.fd == -1)
	{
		perror("Error:\nduring creat_file_descriptor");
		exit(EXIT_FAILURE);
	}
	
}

static void	fork_here_doc(char *delimiter, t_token **tokens,
	t_data **data_array, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(delimiter, tokens, data_array, i);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("Error:\nduring fork_here_doc");
		exit(EXIT_FAILURE);
	}
}

void	here_doc(t_token *tokens, t_data **redirect, int i)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			fork_here_doc(current->value, &tokens, redirect, i);
			printf("name: %s\n", redirect[i]->infile.name);
			printf("fd: %d\n\n", redirect[i]->infile.fd);
		}
		current = current->next;
	}
}*/
