/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_content_var_in_heredoc.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:21 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 12:45:44 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*append_content(char *current_content, const char *new_part)
{
	char	*new_content;

	if (current_content == NULL)
		return (ft_strdup(new_part));
	new_content = ft_strjoin(current_content, new_part);
	free(current_content);
	return (new_content);
}

static char	*process_list_content(t_list *list_content, t_list *list_vars)
{
	char	*new_content;

	new_content = NULL;
	while (list_content)
	{
		new_content = append_content(new_content,
				(char *)list_content->content);
		if (new_content == NULL)
			return (NULL);
		if (list_vars)
		{
			new_content = append_content(
					new_content, (char *)list_vars->content);
			if (new_content == NULL)
				return (NULL);
			list_vars = list_vars->next;
		}
		list_content = list_content->next;
	}
	return (new_content);
}

char	*replace_content(t_list *list_content, t_list *list_vars)
{
	char	*new_content;
	char	*tmp;

	new_content = process_list_content(list_content, list_vars);
	if (new_content == NULL)
		return (NULL);
	tmp = ft_strjoin(new_content, "\n");
	free(new_content);
	new_content = tmp;
	return (new_content);
}

// char	*replace_content(t_list *list_content, t_list *list_vars)
// {
// 	char	*new_content;
// 	char	*tmp;

// 	new_content = NULL;
// 	tmp = NULL;
// 	while (list_content)
// 	{
// 		if (new_content == NULL)
// 			new_content = ft_strdup((char *)list_content->content);
// 		else
// 		{
// 			tmp = ft_strjoin(new_content, (char *)list_content->content);
// 			free(new_content);
// 			new_content = tmp;
// 		}
// 		if (new_content == NULL)
// 			return (NULL);
// 		if (list_vars)
// 		{
// 			tmp = ft_strjoin(new_content, (char *)list_vars->content);
// 			free(new_content);
// 			new_content = tmp;
// 			list_vars = list_vars->next;
// 		}
// 		list_content = list_content->next;
// 	}
// 	tmp = ft_strjoin(new_content, "\n");
// 	free(new_content);
// 	new_content = tmp;
// 	return (new_content);
// }