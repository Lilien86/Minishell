/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_random_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:44:41 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 10:09:54 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_while_loop(int *i, const char *random_chars,
	char *filename, int fd)
{
	unsigned char	random_byte;

	while (*i < FILENAME_LENGTH)
	{
		if (read(fd, &random_byte, sizeof(random_byte)) != sizeof(random_byte))
		{
			perror("Error:\n Could not read from /dev/urandom\n");
			exit(EXIT_FAILURE);
		}
		filename[*i] = random_chars[random_byte % (strlen(random_chars))];
		(*i)++;
	}
}

char	*generate_random_filename(void)
{
	int			fd;
	char		*filename;
	const char	*random_chars;
	int			i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		perror("Error when opening /dev/urandom");
		exit(EXIT_FAILURE);
	}
	filename = ft_calloc((FILENAME_LENGTH + 1), sizeof(char));
	if (filename == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	random_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrst"
		"uvwxyz0123456789-_";
	i = 0;
	handle_while_loop(&i, random_chars, filename, fd);
	filename[FILENAME_LENGTH] = '\0';
	close(fd);
	return (filename);
}
