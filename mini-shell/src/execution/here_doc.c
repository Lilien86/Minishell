/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/04/10 11:18:33 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_here_doc_in_file(char *content, int fd)
{
	if (fd < 0)
	{
		perror("Error:\nduring write_here_doc_in_file\n");
		exit(EXIT_FAILURE);
	}
	if (content == NULL)
	{
		perror("Error:\nduring write_here_doc_in_file\n");
		exit(EXIT_FAILURE);
	}
	write(fd, content, ft_strlen(content));
}

/*static void	creat_file_descriptor(t_minishell *shell, int i)
{
	char	*filename;

	filename = generate_random_filename();
	shell->redirect_array[i].infile.name = ft_calloc(sizeof(char),
			(strlen(filename) + strlen("/tmp/") + 1));
	if (shell->redirect_array[i].infile.name == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		free(filename);
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
	shell->redirect_array[i].infile.name = ft_strncpy
		(shell->redirect_array[i].infile.name, "/tmp/", ft_strlen("/tmp/"));
	shell->redirect_array[i].infile.name = ft_strcat
		(shell->redirect_array[i].infile.name, filename);
	printf("%s\n", shell->redirect_array[i].infile.name);
	shell->redirect_array[i].infile.fd = open
		(shell->redirect_array[i].infile.name, O_CREAT | O_WRONLY, 0777);
	if (shell->redirect_array[i].infile.fd < 0)
	{
		perror("Error:\nduring creat_file_descriptor");
		free(filename);
		free_minishell(shell);
		exit (EXIT_FAILURE);
	}
	free(filename);
}*/

void	generate_and_assign_filename(t_minishell *shell, int i)
{
	char	*filename;

	filename = generate_random_filename();
	shell->redirect_array[i].infile.name = ft_calloc(sizeof(char),
			(strlen(filename) + strlen("/tmp/") + 1));
	if (shell->redirect_array[i].infile.name == NULL)
	{
		perror("Erreur:\n during write_here_doc_in_file\n");
		free(filename);
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
	shell->redirect_array[i].infile.name = ft_strncpy
		(shell->redirect_array[i].infile.name, "/tmp/", ft_strlen("/tmp/"));
	shell->redirect_array[i].infile.name = ft_strcat
		(shell->redirect_array[i].infile.name, filename);
	printf("%s\n", shell->redirect_array[i].infile.name);
	free(filename);
}

void	open_file_and_handle_errors(t_minishell *shell, int i)
{
	shell->redirect_array[i].infile.fd = open
		(shell->redirect_array[i].infile.name, O_CREAT | O_WRONLY, 0777);
	if (shell->redirect_array[i].infile.fd < 0)
	{
		perror("Error:\nduring creat_file_descriptor");
		free_minishell(shell);
		exit (EXIT_FAILURE);
	}
}

void	fork_here_doc(char *delimiter, t_minishell *shell, int i)
{
	pid_t	pid;
	int		status;

	generate_and_assign_filename(shell, i);
	open_file_and_handle_errors(shell, i);
	pid = fork();
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

void	here_doc(t_token *current, t_minishell *shell, int i)
{
	if (current->next == NULL)
	{
		ft_printf("Error:\nNo delimiter for here_doc\n");
		free_minishell(shell);
		exit(EXIT_FAILURE);
	}
	current = current->next;
	fork_here_doc(current->value, shell, i);
	printf("name: %s\n", shell->redirect_array[i].infile.name);
	printf("fd: %d\n\n", shell->redirect_array[i].infile.fd);
}
