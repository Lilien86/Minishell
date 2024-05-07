#include "../minishell.h"

int	check_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0
		&& cmd[3] == '\0')
		return (1);
	else
		return (0);
}

int	check_redirect_in_to_pipe(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	current = current->next;
	if (current == NULL)
		return (0);
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
			return (0);
		else if (current->type == TOKEN_REDIRECT_IN)
			return (1);
		current = current->next;
	}
	return (0);
}

char	**convert_linked_list_to_array(t_token *head)
{
	int				count;
	char			**array;
	t_token			*current;
	int				i;

	i = 0;
	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	array = ft_calloc((size_t)(count + 1), sizeof(char *));
	if (array == NULL)
		error_exit("Memory allocation failed", NULL);
	array[count] = NULL;
	current = head;
	while (i < count)
	{
		array[i] = current->value;
		current = current->next;
		i++;
	}
	return (array);
}

t_token	*convert_argv_to_list(int argc, char **argv)
{
	t_token	*head;
	t_token	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (i < argc)
	{
		tmp = ft_calloc(sizeof(t_list), 1);
		if (!tmp)
			return (NULL);
		tmp->value = argv[argc - 1];
		tmp->next = head;
		head = tmp;
		argc--;
	}
	return (head);
}
