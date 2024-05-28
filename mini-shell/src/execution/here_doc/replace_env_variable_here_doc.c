#include "../../minishell.h"

static char	*replace_content(t_list *list_content, t_list *list_vars)
{
	char	*new_content;
	char	*tmp;

	new_content = NULL;
	tmp = NULL;
	while (list_content)
	{
		if (new_content == NULL)
			new_content = ft_strdup((char *)list_content->content);
		else
		{
			tmp = ft_strjoin(new_content, (char *)list_content->content);
			free(new_content);
			new_content = tmp;
		}
		if (new_content == NULL)
			return (NULL);
		if (list_vars)
		{
			tmp = ft_strjoin(new_content, (char *)list_vars->content);
			free(new_content);
			new_content = tmp;
			list_vars = list_vars->next;
		}
		list_content = list_content->next;
	}
	tmp = ft_strjoin(new_content, "\n");
	free(new_content);
	new_content = tmp;
	return (new_content);
}

// const char	*here_doc_replace_var_env(const char *content, t_minishell *shell)
// {
// 	t_pos_len	*dollars;
// 	t_list		*list_content;
// 	t_list		*list_vars;
// 	char		*new_content;
// 	int			j;
// 	int			i;

// 	i = 0;
// 	j = 0;
// 	new_content = NULL;
// 	if (content == NULL)
// 		return (NULL);
// 	dollars = ft_calloc((size_t)counter_dollars(content), sizeof(t_pos_len));
// 	if (dollars == NULL)
// 		return (content);
// 	while (content[i] != '\0')
// 	{
// 		if (content[i] == '$')
// 		{
// 			dollars[j].pos = i;
// 			dollars[j].len = len_to_dollars((const char *)content, i);
// 			j++;
// 		}
// 		i++;
// 	}
// 	list_content = fill_content_enouth_variable_env(
// 			content, dollars, counter_dollars(content));
// 	list_vars = replace_env_variable(
// 			content, dollars, counter_dollars(content), shell);
// 	new_content = replace_content(list_content, list_vars);
// 	ft_free_lst(list_vars);
// 	ft_free_lst(list_content);
// 	return (new_content);
// }

static void	allocate_and_fill_dollars(const char *content, t_pos_len **dollars_ptr)
{
	t_pos_len	*dollars;
	int			i;
	int			j;

	dollars = (t_pos_len *)ft_calloc(
			(size_t)counter_dollars(content), sizeof(t_pos_len));
	*dollars_ptr = dollars;
	if (dollars == NULL)
		return ;
	i = 0;
	j = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$')
		{
			dollars[j].pos = i;
			dollars[j].len = len_to_dollars(content, i);
			j++;
		}
		i++;
	}
}

static void	process_content_and_vars(const char *content, t_pos_len *dollars,
								t_minishell *shell, char **new_content)
{
	t_list	*list_content;
	t_list	*list_vars;

	list_content = fill_content_enough_variable_env(
			content, dollars, counter_dollars(content));
	list_vars = replace_env_variable(
			content, dollars, counter_dollars(content), shell);
	*new_content = replace_content(list_content, list_vars);
	ft_free_lst(list_vars);
	ft_free_lst(list_content);
}

const char	*here_doc_replace_var_env(const char *content, t_minishell *shell)
{
	t_pos_len	*dollars;
	char		*new_content;

	dollars = NULL;
	new_content = NULL;
	if (content == NULL)
		return (NULL);
	allocate_and_fill_dollars(content, &dollars);
	if (dollars == NULL)
		return (content);
	process_content_and_vars(content, dollars, shell, &new_content);
	free(dollars);
	return (new_content);
}
