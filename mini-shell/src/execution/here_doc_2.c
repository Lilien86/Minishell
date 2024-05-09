#include "../minishell.h"

void	write_here_doc_in_file(char *content, int fd, t_minishell *shell)
{
	if (fd < 0)
	{
		perror("Error:\nduring write_here_doc_in_file\n");
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (content == NULL)
	{
		ft_printf("here_document at line 1 delimited by EOF\n");
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	write(fd, content, ft_strlen(content));
}

static char	*generate_and_assign_filename(t_minishell *shell)
{
	char	*filename;
	char	*final_path;

	filename = generate_random_filename();
	final_path = ft_calloc(sizeof(char),
			(strlen(filename) + strlen("/tmp/") + 1));
	if (final_path == NULL)
	{
		perror("Error:\n during write_here_doc_in_file\n");
		free(filename);
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	final_path = ft_strncpy
		(final_path, "/tmp/", ft_strlen("/tmp/"));
	final_path = ft_strcat
		(final_path, filename);
	free(filename);
	return (final_path);
}

static int	open_file_and_handle_errors(t_minishell *shell, t_file here_doc_cpy)
{
	int	fd;

	fd = open (here_doc_cpy.name, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
	{
		perror("Error:\nduring creat_file_descriptor");
		free_minishell(shell);
		shell->exit_status = 1;
		exit (EXIT_FAILURE);
	}
	return (fd);
}

static t_file fork_here_doc(char *delimiter, t_minishell *shell)
{
	pid_t	pid;
	int		status;
	t_file	*here_doc_cpy;

	here_doc_cpy = malloc(sizeof(t_file)); // Allocate memory on the heap
	if (here_doc_cpy == NULL)
	{
		perror("Error:\nduring fork_here_doc\n");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	here_doc_cpy->name = generate_and_assign_filename(shell);
	here_doc_cpy->fd = open_file_and_handle_errors(shell, *here_doc_cpy);
	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(shell, *here_doc_cpy, delimiter);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("Error:\nduring fork_here_doc");
		free(here_doc_cpy);
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	return (*here_doc_cpy);
}


t_file	here_doc_2(t_token *current, t_minishell *shell)
{
	t_file	here_doc;

	if (current->next == NULL)
	{
		ft_printf("Error:\nNo delimiter for here_doc\n");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	current = current->next;
	here_doc = fork_here_doc(current->value, shell);
	return (here_doc);
}