#include "../../minishell.h"

static char	*read_and_process_line(char *delimiter, char *here_doc_content)
{
	char	*line;

	line = read_line(delimiter);
	if (line == NULL)
		return (NULL);
	here_doc_content = update_here_doc_content(line, here_doc_content);
	return (here_doc_content);
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

	while (1)
	{
		if (g_exit_signal == 1)
		{
			g_exit_signal = 0;
			free(*here_doc_content);
			free_minishell(shell);
			free(here_doc.name);
			close(here_doc.fd);
			ft_printf("\n");
			exit(131);
		}
		temp = read_and_process_line(delimiter, *here_doc_content);
		if (temp == NULL)
		{
			free(temp);
			*here_doc_content = ft_strjoin(*here_doc_content, "\n");
			break ;
		}
		*here_doc_content = temp;
	}
}

void	write_here_doc(t_minishell *shell, t_file here_doc,
	char *here_doc_content, int replace_env)
{
	char	*here_doc_content_env;

	here_doc_content_env = NULL;
	if (replace_env != 1)
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
	if (here_doc_content != NULL)
		free(here_doc_content);
	if (here_doc_content_env != NULL)
		free(here_doc_content_env);
	exit(EXIT_SUCCESS);
}

void	handle_here_doc(t_minishell *shell, t_file here_doc,
		char *delimiter, int replace_env)
{
	char	*here_doc_content;

	here_doc_content = NULL;
	init_signals();
	read_here_doc(shell, here_doc, delimiter, &here_doc_content);
	write_here_doc(shell, here_doc, here_doc_content, replace_env);
}

// void	handle_here_doc(t_minishell *shell, t_file here_doc, char *delimiter,
// 		int replace_env)
// {
// 	char	*here_doc_content;
// 	char	*here_doc_content_env;
// 	char	*temp;

// 	init_signal_handlers();
// 	signal(SIGINT, handle_sigint_here_doc);
// 	here_doc_content = NULL;
// 	here_doc_content_env = NULL;
// 	while (1)
// 	{
// 		if (g_exit_signal == 1)
// 		{
// 			g_exit_signal = 0;
// 			free(here_doc_content);
// 			free_minishell(shell);
// 			free(here_doc.name);
// 			close(here_doc.fd);
// 			ft_printf("\n");
// 			exit(131);
// 		}
// 		temp = read_and_process_line(delimiter, here_doc_content);
// 		if (temp == NULL)
// 		{
// 			free(temp);
// 			here_doc_content = ft_strjoin(here_doc_content, "\n");
// 			break ;
// 		}
// 		here_doc_content = temp;
// 	}
// 	if (replace_env != 1)
// 	{
// 		here_doc_content_env = (char *)here_doc_replace_var_env(
// 				here_doc_content, shell);
// 		write_here_doc_in_file(here_doc_content_env, here_doc.fd, shell);
// 	}
// 	else
// 		write_here_doc_in_file(here_doc_content, here_doc.fd, shell);
// 	free_minishell(shell);
// 	free(here_doc.name);
// 	close(here_doc.fd);
// 	if (here_doc_content != NULL)
// 		free(here_doc_content);
// 	if (here_doc_content_env != NULL)
// 		free(here_doc_content_env);
// 	exit(EXIT_SUCCESS);
// }
