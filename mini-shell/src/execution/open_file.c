#include "../minishell.h"

static void	handle_error_infile(t_file *file, t_minishell *shell, int index)
{
	if (file->fd == -1 && file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 1)
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].infile.fd = -2;
		return ;
	}
	else if (file->fd == -1 && file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].infile.fd = -2;
		return ;
	}
}

void	open_file_in(t_file *file, int is_append, t_minishell *shell, int index)
{
	//char	*path;
	(void)is_append;
	if (file->name != NULL)
	{
		file->fd = open(file->name, O_RDONLY, 0644);
		handle_error_infile(file, shell, index);
	}
}

static void	handle_error_outfile(t_file *file, t_minishell *shell, int index)
{
	if (file->fd == -1 && file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 1)
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].outfile.fd = -2;
		return ;
	}
	else if (file->fd == -1 && file_exist_in_directory(get_variable_path(shell->env),
			file->name) == 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		shell->exit_status = 1;
		shell->redirect_array[index].outfile.fd = -2;
		return ;
	}
}

void	open_file_out(t_file *file, t_minishell *shell,
	int index)
{
	//char	*path;

	if (file->name != NULL)
	{
		if (file_exist_in_directory(get_variable_path(shell->env),
				file->name) == 1)
			file->fd = open(file->name, O_WRONLY);
		else
			file->fd = open(file->name, O_WRONLY | O_CREAT, 0644);
		handle_error_outfile(file, shell, index);
	}
}

void	open_file_out_append(t_file *file, t_minishell *shell,
	int index)
{
	//char	*path;

	if (file->name != NULL)
	{
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		handle_error_outfile(file, shell, index);
	}
}

