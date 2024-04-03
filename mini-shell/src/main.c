#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = ft_copy_tab(envp);
	if (!env)
		return (1);
	read_input(&env);
	ft_free_tab(env);
	return (0);
}
