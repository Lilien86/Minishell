/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_random_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:52:25 by lauger            #+#    #+#             */
/*   Updated: 2024/04/02 11:55:22 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define FILENAME_LENGTH 10

void	handle_while_loop(int *i, const char *random_chars, char *filename, int fd)
{
	unsigned char random_byte;

	while (*i < FILENAME_LENGTH)
	{
		if (read(fd, &random_byte, sizeof(random_byte)) != sizeof(random_byte))
		{
			perror("Erreur lors de la lecture de /dev/urandom");
			exit(EXIT_FAILURE);
		}
		filename[*i] = random_chars[random_byte % (strlen(random_chars))];
		(*i)++;
	}
}

char* generate_random_filename()
{
	int			fd;
	char		*filename;
	const char	*random_chars;
	int			i;
	
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture de /dev/urandom");
		exit(EXIT_FAILURE);
	}
	filename = (char*)malloc((FILENAME_LENGTH + 1) * sizeof(char));
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
