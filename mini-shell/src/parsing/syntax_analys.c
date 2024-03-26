#include "../minishell.h"

static size_t	ft_listsize(t_token *lst)
{
	size_t	cnt;

	cnt = 0;
	while (lst != NULL)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}

/*static void	print_list(t_token *head)
{
	t_token *current = head;
	while (current != NULL)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}*/

void	syntax_analys(t_token *tokens)
{
	t_data		*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		return ;
	data->h_tokens = tokens;
	data->size = ft_listsize(tokens);

	//print_list(data->h_tokens);
	//ft_printf("size---> %d\n", data->size);
	identify_cmds_redirec(data);
}
