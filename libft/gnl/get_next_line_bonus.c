/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:35:35 by lauger            #+#    #+#             */
/*   Updated: 2023/12/12 10:09:26 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_verif(char **buffer, char **line)
{
	*line = ft_calloc(1, 1);
	if (*buffer != NULL)
	{
		*line = ft_strjoin(*line, *buffer);
		free(*buffer);
		*buffer = NULL;
	}
	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (*buffer == NULL || *line == NULL)
	{
		if (*line)
			free(*line);
		if (*buffer)
			free(*buffer);
		*buffer = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	int			r;

	if (ft_verif(&buffer[fd], &line))
		return (NULL);
	while (check_str_char(line, buffer[fd]) == 0)
	{
		r = read(fd, buffer[fd], BUFFER_SIZE);
		if (r <= 0)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
			if (*line)
				return (line);
			free(line);
			return (NULL);
		}
		buffer[fd][r] = 0;
		line = ft_strjoin(line, buffer[fd]);
	}
	return (line);
}
