#include "minishell.h"

t_minishell *init_minishell(char **envp)
{
    t_minishell *shell = malloc(sizeof(t_minishell));
    if (!shell)
        return (NULL);
    
    shell->env = copy_environment(envp);
	if (!shell->env)
		return (NULL);
    shell->tokens = NULL;
    shell->input = NULL;
    shell->history_index = 0;
    init_history(shell->history);

    return (shell);
}

void free_minishell(t_minishell *shell)
{
    if (!shell) 
		return ;

    ft_free_tab(shell->env);
    free_tokens(&(shell->tokens));
    free(shell->input);
    free_history(shell->history);
    free(shell);
}
