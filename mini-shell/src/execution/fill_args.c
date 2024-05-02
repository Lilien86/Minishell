/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:31:32 by lauger            #+#    #+#             */
/*   Updated: 2024/04/30 13:39:44 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
	{
		printf("Le tableau argv est NULL.\n");
		return ;
	}
	while (argv[i] != NULL)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	count_words_in_token(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->type == TOKEN_WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	error_exit(char *message, t_minishell *shell)
{
	perror(message);
	shell->exit_status = 1;
	free_minishell(shell);
	exit(EXIT_FAILURE);
}

void	handle_word(t_minishell *shell, t_token **current, int *i)
{
	int		j;
	int		word_count;
	char	**new_argv;

	word_count = count_words_in_token(*current);
	new_argv = ft_calloc(sizeof(char *), (size_t)(word_count + 1));
	if (new_argv == NULL)
		error_exit("Error:\nduring handle_word\n", shell);
	j = 0;
	while (*current != NULL && (*current)->type == TOKEN_WORD)
	{
		new_argv[j] = ft_strdup((*current)->value);
		if (new_argv[j] == NULL)
			error_exit("Error:\nduring handle_word\n", shell);
		j++;
		*current = (*current)->next;
	}
	new_argv[j] = NULL;
	if (shell->redirect_array[*i].argv != NULL)
		free_argv(shell->redirect_array[*i].argv);
	shell->redirect_array[*i].argv = new_argv;
}
