#include "../../minishell.h"

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

static t_pos_len	*allocate_and_fill_dollars(const char *content, t_pos_len *dollars_ptr)
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
	new_content = process_content_and_vars(content, dollars, shell, new_content);
	free(dollars);
	return (new_content);
}
