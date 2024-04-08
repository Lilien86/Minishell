/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/04/08 11:01:05 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_here_doc_in_file(char *content, int fd, char *fullpath)
{
	ft_printf("\n+++++namefile : %s\n", fullpath);
	ft_printf("+++++fd : %d\n\n", fd);
	write(fd, content, strlen(content));
	//free(fullpath);
}

static void handle_here_doc(t_minishell *shell, int i, char *delimiter)
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
	write_here_doc_in_file(here_doc_content, shell->redirect_array[i].infile.fd, shell->redirect_array[i].infile.name);
	free_minishell(shell);
	free(here_doc_content);
	exit(0);
}

static void	creat_file_descriptor(t_minishell *shell, int i)
{
	char	*filename;

	filename = generate_random_filename();
	shell->redirect_array[i].infile.name = ft_calloc(sizeof(char) , (strlen(filename) + strlen("/tmp/") + 1));
	if (shell->redirect_array[i].infile.name == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		free(filename);
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
	shell->redirect_array[i].infile.name = ft_strncpy(shell->redirect_array[i].infile.name, "/tmp/", ft_strlen("/tmp/"));
	shell->redirect_array[i].infile.name = ft_strcat(shell->redirect_array[i].infile.name, filename);
	printf("%s\n", shell->redirect_array[i].infile.name);
	shell->redirect_array[i].infile.fd = open(shell->redirect_array[i].infile.name, O_CREAT | O_WRONLY, O_APPEND, 0777);
	if (shell->redirect_array[i].infile.fd < 0)
	{
		perror("Error:\nduring creat_file_descriptor");
		free(filename);
		free_minishell(shell);
		exit (EXIT_FAILURE);
	}
	free(filename);
}

void	fork_here_doc(char *delimiter, t_minishell *shell, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	creat_file_descriptor(shell, i);
	if (pid == 0)
	{
		handle_here_doc(shell, i, delimiter);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("Error:\nduring fork_here_doc");
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
}

void	here_doc(t_token *tokens, t_minishell *shell, int i)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			fork_here_doc(current->value, shell, i);
			printf("name: %s\n", shell->redirect_array[i].infile.name);
			printf("fd: %d\n\n", shell->redirect_array[i].infile.fd);
		}
		current = current->next;
	}
}
