#include "minishell.h"

int	g_exit_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;
	int			exit_status;

	(void)argc;
	(void)argv;
	shell = init_minishell(envp);
	if (!shell)
		return (1);
	init_signal_handlers();
	read_input(shell);
	exit_status = shell->exit_status;
	free_minishell(shell);
	return (exit_status);
}
