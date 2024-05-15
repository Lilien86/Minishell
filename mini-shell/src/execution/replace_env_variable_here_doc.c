#include "../minishell.h"

// static char *replace_content(t_list *list_content, t_list *list_vars)
// {
// 	char	*new_content;

// 	new_content = NULL;
// 	while (list_content)
// 	{
// 		if (new_content == NULL)
// 			new_content = ft_strdup((char *)list_content->content);
// 		else
// 			new_content = ft_strjoin(new_content, (char *)list_content->content);
// 		if (new_content == NULL)
// 			return (NULL);
// 		if (list_vars)
// 		{
// 			new_content = ft_strjoin(new_content, (char *)list_vars->content);
// 			list_vars = list_vars->next;
// 		}
// 		list_content = list_content->next;
// 	}
// 	new_content = ft_strjoin(new_content, "\n");
// 	return (new_content);
// }


t_list *fill_content_enouth_variable_env(const char *content, t_pos_len *dollars, int num_vars)
{
	int		i;
	t_list	*list;
	int		start;
	char	*sub;

	i = 0;
	list = NULL;
	start = 0;
	while (i < num_vars)
	{
		if (dollars[i].pos > start)
		{
			sub = ft_substr(content, (unsigned int)start, (size_t)(dollars[i].pos) - (size_t)start);
			if (sub == NULL)
				return (NULL);
			ft_lstadd_back(&list, ft_lstnew(sub));
		}
		start = dollars[i].pos + dollars[i].len;
		i++;
	}
	if ((size_t)start < ft_strlen(content))
	{
		sub = ft_substr(content, (unsigned int)start, (size_t)ft_strlen(content) - (size_t)start);
		if (sub == NULL)
			return (NULL);
		ft_lstadd_back(&list, ft_lstnew(sub));
	}
	return (list);
}

static t_list	*replace_env_variable(const char *content, t_pos_len *dollars, int num_vars, t_minishell *shell)
{
	int		i;
	t_list	*list;
	char	*var;

	i = 0;
	list = NULL;
	var = NULL;
	while (i < num_vars)
	{
		var = substitute_var(ft_substr(content, (unsigned int)dollars[i].pos, (size_t)dollars[i].len), shell->env, shell);
		if (var == NULL)
			return (NULL);
		ft_lstadd_back(&list, ft_lstnew(var));
		i++;
	}
	return (list);
}

static char *replace_content(t_list *list_content, t_list *list_vars)
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

const char  *here_doc_replace_var_env(const char *content, t_minishell *shell)
{
	t_pos_len	*dollars;
	t_list		*list_content;
	t_list		*list_vars;
	char		*new_content;
	int			j;
	int			i;

	i = 0;
	j = 0;
	new_content = NULL;
	if (content == NULL)
		return (NULL);
	dollars = ft_calloc((size_t)counter_dollars(content), sizeof(t_pos_len));
	if (dollars == NULL)
		return (content);
	while(content[i] != '\0')
	{
		if (content[i] == '$')
		{
			dollars[j].pos = i;
			dollars[j].len = len_to_dollars((const char *)content, i);
			j++;
		}
		i++;
	}
	list_content = fill_content_enouth_variable_env(content, dollars, counter_dollars(content));
	list_vars = replace_env_variable(content, dollars, counter_dollars(content), shell);
	new_content = replace_content(list_content, list_vars);
	ft_free_lst(list_vars);
	ft_free_lst(list_content);
	return (new_content);
}