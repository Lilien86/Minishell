#include "../minishell.h"

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

void	run_here_doc(t_minishell *shell)
{
	t_token		*current;
	t_file		**tab_here_doc;
	int			i;
	int			j;

	i = 0;
	j = 0;
	current = shell->tokens;
	tab_here_doc = ft_calloc(((size_t)shell->nb_cmds), sizeof(t_file *));
	if (tab_here_doc == NULL)
		error_exit("Error malloc here_doc", shell);
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (j == 0)
			{
				tab_here_doc[i] = ft_calloc((size_t)counter_here_doc(current),
						sizeof(t_file));
				if (tab_here_doc[i] == NULL)
					error_exit("Error malloc here_doc", shell);
			}
			tab_here_doc[i][j] = here_doc(current, shell);
			j++;
		}
		else if (current->type == TOKEN_PIPE)
		{
			i++;
			j = 0;
		}
		current = current->next;
	}
	shell->tab_here_doc = tab_here_doc;
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
