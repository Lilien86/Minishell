/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/03/27 13:24:32 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_here_doc
{
	int		fd;
	char	*filename;
	char	*line;
}	t_here_doc;

void	init_here_doc(t_here_doc *here_doc)
{
	here_doc->fd = -1;
	here_doc->filename = NULL;
	here_doc->line = NULL;
}

static void	handle_here_doc(char *delimiter)
{
	static char		*buff;
	char			*tmp;
	t_here_doc		*here_doc;
	
	here_doc->filename = "/tmp/proute";
	here_doc->fd = open(here_doc->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	here_doc->line = NULL
	
	while (TRUE)
	{
		
	}
		
}

void	syntax_analys(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			handle_here_doc(current->value);
		}
		current = current->next;
	}
}