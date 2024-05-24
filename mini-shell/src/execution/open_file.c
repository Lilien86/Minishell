#include "../minishell.h"

static char	*get_variable_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			path = ft_strdup(env[i] + 4);
			if (path == NULL)
			{
				perror("Error malloc path");
				exit(EXIT_FAILURE);
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}

static int	file_exist_in_directory(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp(entry->d_name, file) == 0)
		{
			closedir(dir);
			free(path);
			return (1);
		}
	}
	closedir(dir);
	free(path);
	return (0);
}

void	open_file_in(t_file *file, int is_append, t_minishell *shell, int status, int index)
{
	char	*path;

	if (file->name != NULL)
	{
		if (is_append)
			file->fd = open(file->name, O_WRONLY | O_APPEND);
		else if (status == 1)
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (status == 0)
			file->fd = open(file->name, O_RDONLY, 0644);
		if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
			&& file_exist_in_directory(get_variable_path(shell->env), file->name) == 1)
		{
			ft_putstr_fd("minishell: Permision denied\n", 2);
			shell->redirect_array[index].infile.fd = -2;
			return ;
		}
		else if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
			&& file_exist_in_directory(get_variable_path(shell->env), file->name) == 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			shell->exit_status = 1;
			shell->redirect_array[index].infile.fd = -2;
			return ;
		}
	}
}

void	open_file_out(t_file *file, int is_append, t_minishell *shell, int status, int index)
{
	char	*path;

	if (file->name != NULL)
	{
		if (is_append)
			file->fd = open(file->name, O_WRONLY | O_APPEND);
		else if (status == 1)
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (status == 0)
			file->fd = open(file->name, O_RDONLY, 0644);
		if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
			&& file_exist_in_directory(get_variable_path(shell->env), file->name) == 1)
		{
			ft_putstr_fd("minishell: Permision denied\n", 2);
			shell->exit_status = 1;
			shell->redirect_array[index].outfile.fd = -2;
			return ;
		}
		else if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
			&& file_exist_in_directory(get_variable_path(shell->env), file->name) == 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			shell->exit_status = 1;
			shell->redirect_array[index].outfile.fd = -2;
			return ;
		}
	}
}
