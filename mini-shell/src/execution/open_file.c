#include "../minishell.h"

static void	handle_error_infile(t_file *file, t_minishell *shell, int index)
{
	if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
		&& file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 1)
	{
		ft_putstr_fd("minishell: Permision denied\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].infile.fd = -2;
		return ;
	}
	else if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
		&& file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].infile.fd = -2;
		return ;
	}
}

void	open_file_in(t_file *file, int is_append, t_minishell *shell,
	int status, int index)
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
		handle_error_infile(file, shell, index);
	}
}

static void	handle_error_outfile(t_file *file, t_minishell *shell, int index)
{
	if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
		&& file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 1)
	{
		ft_putstr_fd("minishell: Permision denied\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].outfile.fd = -2;
		return ;
	}
	else if (file->fd == -1 && check_redirect_in_to_pipe(shell->tokens) == 0
		&& file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].outfile.fd = -2;
		return ;
	}
}

void	open_file_out(t_file *file, int is_append, t_minishell *shell,
	int status, int index)
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
		handle_error_outfile(file, shell, index);
	}
}

