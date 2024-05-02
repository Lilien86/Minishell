#include "../minishell.h"

int	read_input(t_minishell *shell)
{
	while (1)
	{
		if (shell->input != NULL)
		{
			free(shell->input);
			shell->input = NULL;
		}
		shell->input = readline("minishell > ");
		if (shell->input == NULL)
		{
			free_minishell(shell);
			exit(0);
		}
		handle_input(shell);
		//free(shell->input);
		free_tokens(&(shell->tokens));
		shell->tokens = NULL;
		free_redirect_array(shell, shell->nb_cmds);
		shell->redirect_array = NULL;
	}
	return (0);
}
