#include "../minishell.h"

void    print_pos_dollars(t_pos_len *dollars, int size)
{
	int     i;

	i = 0;
	while (i < size)
	{
		printf("dollars[%d] --> pos/%d size/%d\n", i, dollars[i].pos, dollars[i].len);
		i++;
	}
	return ;
}

int  counter_dollars(const   char *content)
{
	int     counter;
	int     i;

	counter = 0;
	i = 0;
	 while(content[i] != '\0')
	{
		if (content[i] == '$')
		{
			counter++;
		}
		i++;
	}
	return (counter);
}

void print_list(t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		printf("%d: %s\n", i++, (char *)list->content);
		list = list->next;
	}
}

int  len_to_dollars(const char *content, int index)
{
	int     len;

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