#include "minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl-C).
 * 
 * This function is called when the SIGINT signal is received. It clears the current input line,
 * writes a newline character to the standard output, and sets up the readline library for a new line.
 * 
 * @param sig The signal number.
 */
void handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief Signal handler for SIGQUIT (Ctrl-\).
 * 
 * This function is called when the SIGQUIT signal is received. It ignores the signal.
 * 
 * @param sig The signal number.
 */
void handle_sigquit(int sig)
{
	(void)sig;
}

/**
 * @brief Initializes the signal handlers.
 * 
 * This function sets up the signal handlers for SIGINT and SIGQUIT.
 */
void init_signal_handlers(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
