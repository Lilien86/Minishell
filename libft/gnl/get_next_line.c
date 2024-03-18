/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:35:35 by lauger            #+#    #+#             */
/*   Updated: 2023/11/23 13:35:44 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buffer;
	char		*line;
	int			r;

	if (ft_verif(&buffer, &line))
		return (NULL);
	while (check_str_char(line, buffer) == 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
		{
			free(buffer);
			buffer = NULL;
			if (*line)
				return (line);
			free(line);
			return (NULL);
		}
		buffer[r] = 0;
		line = ft_strjoin(line, buffer);
	}
	return (line);
}
