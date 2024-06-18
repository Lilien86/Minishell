/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_content_heredoc_with_variable.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:10 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 14:07:09 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	add_substring_to_list(const char *content, int start, int end,
	t_list **list)
{
	char	*sub;

	sub = ft_substr(content, (unsigned int)start, (size_t)(end - start - 1));
	if (sub == NULL)
		return (1);
	ft_lstadd_back(list, ft_lstnew(sub));
	return (0);
}

static t_list	*string_enough_var(const char *content, t_pos_len *dollars,
	int num_vars, t_list **list)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < num_vars)
	{
		if (dollars[i].pos > start)
		{
			if (add_substring_to_list(content, (start),
					dollars[i].pos, list) == 1)
				return (NULL);
		}
		start = dollars[i].pos + dollars[i].origin_len;
		i++;
	}
	if ((size_t)start < ft_strlen(content))
		add_substring_to_list(content, (start),
			(int)ft_strlen(content), list);
	return (*list);
}

t_list	*fill_content_enough_variable_env(const char *content,
	t_pos_len *dollars, int num_vars)
{
	t_list	*list;

	list = NULL;
	if (content == NULL || dollars == NULL)
		return (NULL);
	list = string_enough_var(content, dollars, num_vars, &list);
	return (list);
}

t_list	*replace_env_variable(const char *content, t_pos_len *dollars,
	int num_vars, t_minishell *shell)
{
	int		i;
	t_list	*list;
	char	*var;
	char	*tmp;

	i = 0;
	list = NULL;
	var = NULL;
	tmp = NULL;
	while (i < num_vars)
	{
		tmp = ft_substr(content, (unsigned int)dollars[i].pos,
				(size_t)dollars[i].len);
		var = substitute_var(tmp, shell->env, shell);
		if (var == NULL)
			return (NULL);
		ft_lstadd_back(&list, ft_lstnew(var));
		free(tmp);
		i++;
	}
	return (list);
}
