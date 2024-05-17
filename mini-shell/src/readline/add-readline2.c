#include "../minishell.h"

// static void unlink_file(t_file **tab_files)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (tab_files && tab_files[i] != NULL)
// 	{
// 		while (tab_files[i][j].name != NULL)
// 		{
// 			printf("Unlinking file: %s\n", tab_files[i][j].name);
// 			unlink(tab_files[i][j].name);
// 			free(tab_files[i][j].name);
// 			tab_files[i][j].name = NULL;
// 			j++;
// 		}
// 		//free(tab_files[i]);
// 		i++;
// 	}
// }
void	free_read(t_minishell *shell)
{
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens != NULL)
	{
		free_tokens(&(shell->tokens));
		shell->tokens = NULL;
	}
	if (shell->redirect_array != NULL)
	{
		free_redirect_array(shell, shell->nb_cmds);
		shell->redirect_array = NULL;
	}
	free_tab_here_doc(shell->tab_here_doc, shell->nb_cmds);
}

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
		free_read(shell);
	}
	return (0);
}

void	print_linked_list(t_token *head)
{
	t_token		*current;
	int			i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		ft_printf("%d Valeur: %s\n", i, current->value);
		i++;
		current = current->next;
	}
}
