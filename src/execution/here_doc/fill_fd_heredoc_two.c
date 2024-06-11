/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd_heredoc_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:43:48 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 10:04:03 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*read_line(char *delimiter)
{
	char	*line;

	line = readline(" > ");
	if (line == NULL)
	{
		if (line != NULL)
			free(line);
		ft_putstr_fd("bash: warning: here-document at line 1 delimited"
			"by end-of-file (wanted `%s')\n", 2);
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		if (line != NULL)
			free(line);
		return (NULL);
	}
	return (line);
}
