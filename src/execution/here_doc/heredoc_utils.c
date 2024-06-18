/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:55:45 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 15:26:46 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_fork_error(t_minishell *shell)
{
	perror("Error:\nduring fork_here_doc");
	free_minishell(shell);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
}

void	handle_parent_process(pid_t pid, t_minishell *shell)
{
	int	status;
	int	term_sig;

	(void)shell;
	waitpid(pid, &status, 0);
	term_sig = WEXITSTATUS(status);
	if (term_sig == 130 || term_sig == 131)
		g_exit_signal = 1;
}
