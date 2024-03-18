/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add-readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:16:29 by lauger            #+#    #+#             */
/*   Updated: 2024/03/18 13:48:24 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	while (1)
	{
		printf("minishell > ");
		input = readline("");
		//printf("-%s-", input);
		if (input == NULL || strcmp(input, "") == 0)
		{
			printf("-%s-", input);
			printf("\n");
			free(input);
			break;
		}

	}
	return (0);
}
