/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_s_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:11 by lauger            #+#    #+#             */
/*   Updated: 2024/04/04 14:31:27 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	counter_cmds(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count + 1);
}

void	fill_s_data(t_token tokens)
{
	int		nb_cmds;
	t_data	*data_array;
	t_token	*current;

	nb_cmds = counter_cmds(&tokens);
	current = &tokens;
	data_array = ft_calloc((nb_cmds), sizeof(t_data));
	if (data_array == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	while (current != NULL)
	{
		if (current->type == TOKEN_WORD)
		{
			//add_word_token(&current->value, &data_array->argv);
		}
		current = current->next;
	}
	
}

/* lilien tu vas devoir looper sur la linke list, quand tu rencontre un pipe tu passe a 
l'index suivant dans data_array et tu passe a l'element suivant dans la linked list doc apres le pipe.
quand tu rencontre un < c'est que l'infile est juste apres, et quand c'et un > le oufile est apres.
Oublie pas d'initailiser le infile et oufile a null comme ca tu sais si il existe, et cheque ussi avec open si tu peu les ouvrire*/