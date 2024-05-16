#include "../minishell.h"

void	free_tab_here_doc(t_file **tab_here_doc, int nb_cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab_here_doc && i < nb_cmds)
	{
		while (tab_here_doc[i] && tab_here_doc[i][j].name!= NULL)
		{
			free(tab_here_doc[i][j].name);
			j++;
		}
		i++;
	}
	j = 0;
	while (tab_here_doc && i < nb_cmds)
	{
		free(tab_here_doc[i]);
		i++;
	}
	free(tab_here_doc);
	tab_here_doc = NULL;
}


static int	counter_here_doc(t_token *tokens)
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

t_file	**run_here_doc(t_minishell *shell)
{
	t_token		*current;
	t_file		**tab_here_doc;
	int			replace_env;
	int			i;
	int			j;

	i = 0;
	j = 0;
	replace_env = 0;
	current = shell->tokens;
	tab_here_doc = ft_calloc(((size_t)shell->nb_cmds), sizeof(t_file *));
	if (tab_here_doc == NULL)
		error_exit("Error malloc here_doc", shell);
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (current->next->quote_type == SINGLE_QUOTE)
				replace_env = 1;
			if (j == 0)
			{
				tab_here_doc[i] = ft_calloc((size_t)counter_here_doc(current),
						sizeof(t_file));
				if (tab_here_doc[i] == NULL)
					error_exit("Error malloc here_doc", shell);
			}
			tab_here_doc[i][j] = here_doc(current, shell, replace_env);
			j++;
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

void	to_choice_here_doc(t_minishell *shell, int *i)
{
	int		j;
	int		nb_here_doc;

	j = 0;
	nb_here_doc = counter_here_doc(shell->tokens);
	while (nb_here_doc != 0 && j != *i)
	{
		close(shell->tab_here_doc[*i][j].fd);
		j++;
	}
	if (shell->tab_here_doc && nb_here_doc != 0)
	{
		close (shell->tab_here_doc[*i][nb_here_doc - 1].fd);
		shell->redirect_array[*i].infile.fd = open (
				shell->tab_here_doc[*i][nb_here_doc - 1].name, O_RDONLY);
		if (shell->tab_here_doc[*i][nb_here_doc - 1].fd == -1)
			error_exit("Error open here_doc", shell);
		shell->redirect_array[*i].infile.name = shell->tab_here_doc[*i][
			nb_here_doc - 1].name;
	}
}
