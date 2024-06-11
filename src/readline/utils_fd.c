/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:32:05 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:32:16 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file_and_handle_errors(t_minishell *shell, t_file here_doc_cpy)
{
	int	fd;

	fd = open (here_doc_cpy.name, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
	{
		perror("Error:\nduring creat_file_descriptor");
		free_minishell(shell);
		shell->exit_status = 1;
		exit (EXIT_FAILURE);
	}
	return (fd);
}
