/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_variable_here_doc.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:52 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 10:12:08 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	find_origin_len(const char *content, int pos)
{
	int	i;
	int	cnt;

	i = pos + 1;
	cnt = 0;
	while (ft_isspace(content[i]) == 0 && content[i] != '\0')
	{
		cnt++;
		i++;
	}
	return (cnt);
}

static t_pos_len	*allocate_and_fill_dollars(const char *content,
	t_pos_len *dollars_ptr)
{
	t_pos_len	*dollars;
	int			i;
	int			j;

	dollars = (t_pos_len *)ft_calloc(
			(size_t)counter_dollars(content), sizeof(t_pos_len));
	dollars_ptr = dollars;
	if (dollars == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$')
		{
			dollars[j].pos = i;
			dollars[j].len = len_to_dollars(content, i);
			dollars[j].origin_len = find_origin_len(content, i);
			ft_printf("origin_len %d\n", dollars[j].origin_len);
			j++;
		}
		i++;
	}
	return (dollars);
}

static void	ft_free_lst_char(t_list *head)
{
	t_list	*current;
	t_list	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->content);
		current->content = NULL;
		free(current);
		current = next_node;
	}
}

static char	*process_content_and_vars(const char *content, t_pos_len *dollars,
								t_minishell *shell, char *new_content)
{
	t_list	*list_content;
	t_list	*list_vars;

	list_content = fill_content_enough_variable_env(
			content, dollars, counter_dollars(content));
	list_vars = replace_env_variable(
			content, dollars, counter_dollars(content), shell);
	new_content = replace_content(list_content, list_vars);
	ft_free_lst(list_vars);
	ft_free_lst_char(list_content);
	return (new_content);
}

const char	*here_doc_replace_var_env(const char *content, t_minishell *shell)
{
	t_pos_len	*dollars;
	char		*new_content;

	dollars = NULL;
	new_content = NULL;
	if (content == NULL)
		return (NULL);
	dollars = allocate_and_fill_dollars(content, dollars);
	if (dollars == NULL)
		return (content);
	new_content = process_content_and_vars(content, dollars,
			shell, new_content);
	free(dollars);
	return (new_content);
}
