/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:28:59 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 11:29:07 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remember_fd_here_doc(t_file *here_doc, t_minishell *shell)
{
	static int			cnt_call = 0;
	static int			fd = 0;
	static t_file		*here_doc_s = NULL;
	static t_minishell	*shell_s = NULL;

	if (cnt_call == 0)
	{
		fd = here_doc->fd;
		here_doc_s = here_doc;
		shell_s = shell;
		cnt_call++;
	}
	else
	{
		close(fd);
		free_minishell(shell_s);
		free(here_doc_s->name);
	}
}
