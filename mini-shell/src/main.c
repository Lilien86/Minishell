/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:49:34 by lauger            #+#    #+#             */
/*   Updated: 2024/03/20 13:52:00 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	read_input();
	
	t_token	*tokens;
	t_token	*temp;
	char	*input;

	(void)ac;
	while (av[1])
	{
		input = ft_strdup(av[1]);
		break ;
	}

	tokens = tokenize(input);
	ft_printf("Tokens:\n");
	temp = tokens;
	while (temp)
	{
		ft_printf("Type: %d, Value: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
	free_tokens(&tokens);*/
	return (0);
}
