/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:31:54 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:31:56 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0
		&& cmd[3] == '\0')
		return (1);
	else
		return (0);
}

int	check_redirect_in_to_pipe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	current = current->next;
	if (current == NULL)
		return (0);
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
			return (0);
		else if (current->type == TOKEN_REDIRECT_IN
			||current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_DOUBLE_REDIRECT_OUT)
			return (1);
		current = current->next;
	}
	return (0);
}

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

t_token	*convert_argv_to_list(int argc, char **argv)
{
	t_token	*head;
	t_token	*tmp;
	int		i;

	head = NULL;
	i = argc - 1;
	while (i >= 0)
	{
		tmp = (t_token *)ft_calloc(sizeof(t_token), 1);
		if (!tmp)
			return (NULL);
		tmp->value = ft_strdup(argv[i]);
		if (tmp->value == NULL)
		{
			free(tmp);
			return (NULL);
		}
		tmp->type = TOKEN_WORD;
		tmp->next = head;
		head = tmp;
		i--;
	}
	return (head);
}
