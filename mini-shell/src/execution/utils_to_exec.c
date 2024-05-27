#include "../minishell.h"

int	counter_dollars(const char *content)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	if (content != NULL)
	{
		while (content[i] != '\0')
		{
			if (content[i] == '$')
				counter++;
			i++;
		}
	}
	return (counter);
}

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d: %s\n", i++, (char *)list->content);
		list = list->next;
	}
}

int	len_to_dollars(const char *content, int index)
{
	int		len;

	len = 0;
	if (content[index] != '$')
		return (0);
	while (content[index] != ' ' && content[index] != '\0')
	{
		index++;
		len ++;
	}
	return (len);
}
