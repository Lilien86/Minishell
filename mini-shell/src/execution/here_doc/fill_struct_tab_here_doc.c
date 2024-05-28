#include "../../minishell.h"

int	counter_here_doc(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_HEREDOC)
			count++;
		if (tokens->type == TOKEN_PIPE)
			break ;
		tokens = tokens->next;
	}
	return (count);
}

static void	init_here_doc_tab(t_file **tab_here_doc, int i,
	t_token *current, t_minishell *shell)
{
	tab_here_doc[i] = ft_calloc(((size_t)counter_here_doc(current) + 1),
			sizeof(t_file *));
	if (tab_here_doc[i] == NULL)
		error_exit("Error malloc here_doc", shell);
}

static void	process_here_doc_token(t_token *current, t_minishell *shell,
	t_file **tab_here_doc, int *i, int *j, int *replace_env)
{
	if (current->next->quote_type != SINGLE_QUOTE)
		*replace_env = 1;
	if (*j == 0)
		init_here_doc_tab(tab_here_doc, *i, current, shell);
	tab_here_doc[*i][*j] = here_doc(current, shell, *replace_env, tab_here_doc);
	tab_here_doc[*i][*j].is_allocated = 1;
	(*j)++;
}

t_file	**fill_tab_here_doc(t_token *current, t_minishell *shell,
	t_file **tab_here_doc, int replace_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next == NULL
				|| current->next->quote_type != TOKEN_WORD)
			{
				ft_putstr_fd("minishell: syntax error"
					" near unexpected token `newline'\n", 2);
				shell->exit_status = 258;
				return (NULL);
			}
			process_here_doc_token(current, shell, tab_here_doc,
				&i, &j, &replace_env);
		}
		else if (current->type == TOKEN_PIPE)
		{
			i++;
			j = 0;
		}
		current = current->next;
	}
	return (tab_here_doc);
}
