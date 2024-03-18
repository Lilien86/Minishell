/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:49:34 by lauger            #+#    #+#             */
/*   Updated: 2024/03/18 10:10:06 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const char	*input = "echo prout > file.txt | cat < file.txt >> file2.txt ; ls -l ; echo $?";
	t_token		*tokens;

	tokens = tokenize(input);
	ft_printf("Tokens:\n");
	while (tokens)
	{
		ft_printf("Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
	free_tokens(&tokens);
	return (0);
}
