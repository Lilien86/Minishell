#include "../minishell.h"

int	counter_dollars(const char *content)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	if (content != NULL)
	{
		while (content[i] != '\0')
		{
			if (content[i] == '$')
				counter++;
			i++;
		}
	}
	return (counter);
}

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d: %s\n", i++, (char *)list->content);
		list = list->next;
	}
}

int	len_to_dollars(const char *content, int index)
{
	int		len;

	len = 0;
	if (content[index] != '$')
		return (0);
	while (content[index] != ' ' && content[index] != '\0')
	{
		index++;
		len ++;
	}
	return (len);
}

char	*get_variable_path(char **env)
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

int	file_exist_in_directory(char *path, char *file)
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
	if (access(file, F_OK) == 0 && access(file, X_OK) == -1)
	{
		closedir(dir);
		free(path);
		return (1);
	}
	closedir(dir);
	free(path);
	return (0);
}

int	is_file(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (-1);
	if (S_ISREG(statbuf.st_mode))
		return (1);
	else if (S_ISDIR(statbuf.st_mode))
		return (0);
	else
		return (-1);
}