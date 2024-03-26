/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmds_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:44:34 by lauger            #+#    #+#             */
/*   Updated: 2024/03/26 11:12:50 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloc_cmds_args(t_token *tokens, int nb_word)
{
	char		**cmds_args;
	t_token		*current_token;
	int			j;

	cmds_args = (char **)ft_calloc((size_t)(nb_word + 1) , sizeof(char *));
	if (cmds_args == NULL)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	current_token = tokens;
	j = 0;
	while (current_token != NULL && j < nb_word)
	{
		cmds_args[j] = current_token->value;
		current_token = current_token->next;
		j++;
	}
	return (cmds_args);
}