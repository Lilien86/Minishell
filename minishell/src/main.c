/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:49:34 by lauger            #+#    #+#             */
/*   Updated: 2024/03/19 11:04:51 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *input = "echo \"Ceci est un 'test' avec des espaces\" && echo \
	'Les guillemets simples fonctionnent aussi'";
    t_token *tokens;
    t_token *temp;

    tokens = tokenize(input);
    ft_printf("Tokens:\n");
    temp = tokens; 
    while (temp) 
	{
        ft_printf("Type: %d, Value: %s\n", temp->type, temp->value);
        temp = temp->next;
    }
    free_tokens(&tokens);
    return (0);
}

