/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:24:42 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 13:25:40 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_exist_in_directory(char *path, char *file)
{
	DIR				*dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}
	if (check_file_in_directory(dir, path, file))
		return (1);
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
