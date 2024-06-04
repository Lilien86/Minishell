/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add-readline2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:53:02 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 13:14:40 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (shell->tab_here_doc != NULL)
	{
		free_tab_here_doc(shell->tab_here_doc, shell->nb_cmds);
		shell->tab_here_doc = NULL;
	}
}

int	read_input(t_minishell *shell)
{
	int	local_exit_status;

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
			local_exit_status = shell->exit_status;
			free_minishell(shell);
			ft_printf("exit\n");
			exit(local_exit_status);
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

void	handle_input(t_minishell *shell)
{
	if (ft_strcmp(shell->input, "") == 0)
		return ;
	process_input(shell);
}

int	check_first_token(t_token *tokens, t_minishell *shell)
{
	if (tokens && (ft_strcmp(tokens->value, "./") == 0
			|| ft_strcmp(tokens->value, "../") == 0
			|| ft_strcmp(tokens->value, ".") == 0
			|| ft_strcmp(tokens->value, "..") == 0))
	{
		ft_putstr_fd("minishell: syntax error: unexpected path\n", 2);
		shell->exit_status = 126;
		return (1);
	}
	return (0);
}

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