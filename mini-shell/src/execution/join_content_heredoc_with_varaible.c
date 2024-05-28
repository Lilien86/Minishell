# include "../minishell.h"

t_list	*fill_content_enouth_variable_env(const char *content,
			t_pos_len *dollars, int num_vars)
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
			sub = ft_substr(content, (unsigned int)start,
					(size_t)(dollars[i].pos) - (size_t)start);
			if (sub == NULL)
				return (NULL);
			ft_lstadd_back(&list, ft_lstnew(sub));
		}
		start = dollars[i].pos + dollars[i].len;
		i++;
	}
	if ((size_t)start < ft_strlen(content))
	{
		sub = ft_substr(content, (unsigned int)start,
				(size_t)ft_strlen(content) - (size_t)start);
		if (sub == NULL)
			return (NULL);
		ft_lstadd_back(&list, ft_lstnew(sub));
	}
	return (list);
}

t_list	*replace_env_variable(const char *content, t_pos_len *dollars,
	int num_vars, t_minishell *shell)
{
	int		i;
	t_list	*list;
	char	*var;

	i = 0;
	list = NULL;
	var = NULL;
	while (i < num_vars)
	{
		var = substitute_var(ft_substr(content, (unsigned int)dollars[i].pos,
					(size_t)dollars[i].len), shell->env, shell);
		if (var == NULL)
			return (NULL);
		ft_lstadd_back(&list, ft_lstnew(var));
		i++;
	}
	return (list);
}