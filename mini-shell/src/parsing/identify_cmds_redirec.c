#include "../minishell.h"

void print_string_array_3d(char ***array)
{
	for (int i = 0; array[i] != NULL; i++) {
		for (int j = 0; array[i][j] != NULL; j++) {
			for (int k = 0; array[i][j][k] != '\0'; k++) {
				printf("%c", array[i][j][k]);
			}
			printf(" ");
		}
		printf("\n");
	}
}

static int	counter_command(t_token *tokens)
{
	t_token	*current;
	t_token	*next;
	int	cnt;
	int	i;

	current = tokens;
	cnt = 0;
	i = 0;
	while (current != NULL)
	{
		next = current->next;
		if (i == 0 && current->type == TOKEN_WORD)
			cnt++;
		else if (current->type != TOKEN_WORD && next->type == TOKEN_WORD)
			cnt++;
		current =current->next;
		i++;
	}
	return (cnt);
}

static int	counter_words(t_token *current, int i)
{
	int			cnt;
	t_token		*cpy_current;
	
	cnt = 0;
	cpy_current = current;
	if (i == 1)
		cnt++;
	while (cpy_current != NULL && cpy_current->type == TOKEN_WORD)
	{
		cnt++;
		cpy_current = cpy_current->next;
	}
	return (cnt);
}

static void	handle_counter_word(t_data *data)
{
	t_token		*current;
	t_token		*next;
	int			nb_word;
	int			i;
	int			j;

	i = 0;
	j = 0;
	nb_word = 0;
	current = data->h_tokens;
	while (current != NULL)
	{
		next = current->next;
		if ((current->type != TOKEN_WORD && next->type == TOKEN_WORD)
			|| (i == 0 && current->type == TOKEN_WORD))
		{
			i++;
			current = current->next;
			nb_word = counter_words(current, i);
			ft_printf("nb-----> %d\n", nb_word);
			data->cmds[j] = alloc_cmds_args(current, nb_word);
			j++;
		}
		else
		{
			current = current->next;
			i++;
		}
	}
}

void	identify_cmds_redirec(t_data *data)
{
	int	nb_cmds;

	nb_cmds = counter_command(data->h_tokens);
	data->cmds = ft_calloc(1, (size_t)(nb_cmds + 1));
	if (data->cmds == NULL)
		return ;
	handle_counter_word(data);
	print_string_array_3d(data->cmds);
}
