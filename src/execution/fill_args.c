/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:31:32 by lauger            #+#    #+#             */
/*   Updated: 2024/06/10 20:07:14 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	append_argv(
		char **temp_argv, char **argv2, t_minishell *shell, int start_index)
{
	int	i;
	int	j;

	i = start_index;
	j = 0;
	while (argv2[j])
	{
		temp_argv[i] = ft_strdup(argv2[j]);
		if (!temp_argv[i])
			error_exit("Error: during strdup in append_argv\n", shell);
		i++;
		j++;
	}
	temp_argv[i] = NULL;
}

void	concate_argv(char ***argv1, char **argv2, t_minishell *shell)
{
	char	**temp_argv;
	int		i;
	int		j;

	temp_argv = ft_calloc(
			ft_tab_len(*argv1) + ft_tab_len(argv2) + 1, sizeof(char *));
	if (!temp_argv)
		error_exit("Error: Memory allocation failed\n", shell);
	i = 0;
	j = 0;
	while ((*argv1)[j])
	{
		temp_argv[i] = ft_strdup((*argv1)[j]);
		if (!temp_argv[i])
			error_exit("Error: during strdup in concate_argv\n", shell);
		i++;
		j++;
	}
	append_argv(temp_argv, argv2, shell, i);
	free_argv(*argv1);
	*argv1 = temp_argv;
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
	{
		concate_argv(&shell->redirect_array[*i].argv, new_argv, shell);
		free_argv(new_argv);
	}
	else
		shell->redirect_array[*i].argv = new_argv;
}
