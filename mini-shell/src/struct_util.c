#include "minishell.h"

int	is_token_redirection(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT
			|| tmp->type == TOKEN_DOUBLE_REDIRECT_OUT || tmp->type == TOKEN_HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*shell;

	shell = (t_minishell *)ft_calloc(sizeof(t_minishell), 1);
	if (!shell)
		return (NULL);
	shell->env = ft_copy_tab(envp);
	if (!shell->env)
		return (NULL);
	shell->tokens = NULL;
	shell->input = NULL;
	shell->history_index = 0;
	shell->nb_cmds = 0;
	shell->redirect_array = NULL;
	init_history(shell->history);
	return (shell);
}

void	free_minishell(t_minishell *shell)
{
	if (!shell)
		return ;
	ft_free_tab(shell->env);
	free_tokens(&(shell->tokens));
	shell->tokens = NULL;
	if (shell->input)
		free(shell->input);
	free_history(shell->history);
	*shell->history = NULL;
	if (shell->redirect_array)
	{
		free_redirect_array (&(shell->redirect_array), shell->nb_cmds);
		shell->redirect_array = NULL;
	}
	free(shell);
	shell = NULL;
}
