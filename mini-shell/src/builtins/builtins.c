#include "../minishell.h"

/**
 * @brief Implements the echo command.
 *
 * This function prints the given arguments to the standard output.
 * If the "-n" flag is provided as the first argument,
 * it suppresses the trailing newline.
 *
 * @param tokens The linked list of tokens representing
 * the command and its arguments.
 */
void	ft_echo(t_token *tokens)
{
	int		newline;
	t_token	*current;

	newline = 1;
	current = tokens->next;
	while (current && is_flag_n(current->value))
	{
		newline = 0;
		current = current->next;
	}
	while (current != NULL)
	{
		ft_printf("%s", current->value);
		current = current->next;
	}
	if (newline)
		ft_printf("\n");
}

/**
 * @brief Implements the cd command.
 *
 * This function changes the current working
 * directory to the specified path.
 * If no path is provided, it changes the directory
 * to the value of the HOME environment variable.
 *
 * @param tokens The linked list of tokens representing
 * the command and its arguments.
 * @param env The array of environment variables.
 */
void	ft_cd(t_token *tokens, char **env)
{
	char	*path;
	int		ret;

	if (tokens->next == NULL)
		path = ft_getenv("HOME", env);
	else
		path = tokens->next->value;
	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
	}
}

/**
 * @brief Implements the pwd command.
 *
 * This function prints the current working directory to the standard output.
 */
void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	else
		ft_printf("minishell: pwd: %s\n", strerror(errno));
}
