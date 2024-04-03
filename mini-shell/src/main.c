#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	t_minishell *shell;

	(void)argc;
	(void)argv;
	shell = init_minishell(envp);
	if (!shell)
		return (1);
    init_signal_handlers();
	read_input(shell);
	free_minishell(shell);
	return (0);
}
