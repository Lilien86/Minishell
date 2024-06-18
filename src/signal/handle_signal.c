/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:25 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/18 12:02:33 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_exit_signal = 1;
	remember_fd_here_doc(NULL, NULL);
	exit(130);
}

void	handle_sigquit_here_doc(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_exit_signal = 2;
	exit(131);
}

void	handle_sigquit_two(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_exit_signal = 131;
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_signal = 130;
}

void	init_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
