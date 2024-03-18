/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:49:34 by lauger            #+#    #+#             */
/*   Updated: 2024/03/18 14:03:57 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Work:
cat file.txt > output.txt
cat << EOF > heredoc.txt Ceci est un texte de test pour heredoc.EOF

Dont Work:
grep 'pattern' < input.txt | sort >> sorted.txt

*/

int	main(void)
{
	char	*input = "echo \"Ceci est un test avec des espaces\" && echo 'Les guillemets simples fonctionnent aussi'";
	
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
