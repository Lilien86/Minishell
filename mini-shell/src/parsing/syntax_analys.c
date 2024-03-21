#include "../minishell.h"

/*static void	init_data(t_data data)
{

}*/

/*static int	ft_lstsize(t_tokens *lst)
{
	int	cnt;

	cnt = 0;
	while (lst != NULL)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}*/

/*static void print_list(t_token *head)
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
	t_data *data = malloc(sizeof(t_data));
	t_token	*temp;

	data->h_tokens = tokens;
	data->size = 0;
	temp = tokens;

	while (temp)
	{
		ft_printf("\nType: %d, Value: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
	//print_list(t_tokens->tokens);
	ft_printf("size---> %d\n", data->size);
}