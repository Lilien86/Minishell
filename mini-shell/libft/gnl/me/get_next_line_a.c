/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:02:53 by roguigna          #+#    #+#             */
/*   Updated: 2024/03/06 14:02:53 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*make_line(char *line)
{
	int	len_line;

	len_line = 0;
	while (line[len_line] != '\n' && line[len_line])
		len_line++;
	if (line[len_line] == '\n')
		line[len_line + 1] = '\0';
	return (line);
}

static char	*keep_end(char *line, char *buf)
{
	int	i;
	int	len_line;
	int	total_len;

	i = 0;
	len_line = 0;
	total_len = ft_strlen(line);
	while (line[len_line] != '\n' && line[len_line])
		len_line++;
	free(buf);
	buf = ft_calloc(total_len - len_line + 2, sizeof(char));
	if (!buf)
	{
		free(line);
		return (0);
	}
	if (line[len_line] == '\n')
		len_line++;
	while (line[len_line + i])
	{
		buf[i] = line[len_line + i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

static int	end_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(int fd, char *save)
{
	char	*buf;
	int		octet;

	octet = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
	{
		free(save);
		return (0);
	}
	while (end_line(save) != 1 && octet > 0)
	{
		octet = read(fd, buf, BUFFER_SIZE);
		if (buf[0] == '\0' && (octet == 0 || octet == -1) && !save[0])
		{
			free(save);
			free(buf);
			return (0);
		}
		buf[octet] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*get_next_line_a(int fd)
{
	static char	*save;
	char		*line;

	if (fd == -12)
	{
		free(save);
		return (0);
	}
	line = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (!save)
	{
		save = ft_calloc(1, sizeof(char));
		if (!save)
			return (0);
	}
	save = get_line(fd, save);
	if (save == 0)
		return (0);
	line = ft_strjoin(line, save);
	save = keep_end(line, save);
	line = make_line(line);
	return (line);
}
