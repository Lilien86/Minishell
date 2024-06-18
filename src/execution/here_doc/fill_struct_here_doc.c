/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:44:13 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 12:19:43 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab_here_doc(t_file **tab_here_doc, int nb_cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab_here_doc && i < nb_cmds)
	{
		j = 0;
		while (tab_here_doc[i] && tab_here_doc[i][j].name != NULL)
		{
			if (is_valid_fd(tab_here_doc[i][j].fd) == 1)
				close(tab_here_doc[i][j].fd);
			unlink(tab_here_doc[i][j].name);
			free(tab_here_doc[i][j].name);
			j++;
		}
		free(tab_here_doc[i]);
		i++;
	}
	i = 0;
	free(tab_here_doc);
}

t_file	**run_here_doc(t_minishell *shell)
{
	t_token		*current;
	t_file		**tab_here_doc;
	int			replace_env;

	replace_env = 0;
	current = shell->tokens;
	tab_here_doc = ft_calloc(((size_t)shell->nb_cmds), sizeof(t_file *));
	if (tab_here_doc == NULL)
		error_exit("Error malloc here_doc", shell);
	fill_tab_here_doc(current, shell, tab_here_doc, replace_env);
	return (tab_here_doc);
}

void	choose_here_doc(t_minishell *shell, int *i, int id_here_doc)
{
	int		j;
	int		nb_here_doc;

	j = 0;
	nb_here_doc = counter_here_doc(shell->tokens);
	while (nb_here_doc != 0 && j < nb_here_doc - 1)
	{
		close(shell->tab_here_doc[*i][j].fd);
		j++;
	}
	if (shell->tab_here_doc && nb_here_doc != 0 && id_here_doc == 0)
	{
		if (shell->exit_status == 1)
			return ;
		close (shell->tab_here_doc[*i][nb_here_doc - 1].fd);
		shell->redirect_array[*i].infile.fd = open (
				shell->tab_here_doc[*i][nb_here_doc - 1].name, O_RDONLY);
		if (shell->tab_here_doc[*i][nb_here_doc - 1].fd == -1)
			error_exit("Error opening here_doc", shell);
		shell->redirect_array[*i].infile.name = shell->tab_here_doc[*i][
			nb_here_doc - 1].name;
	}
}
