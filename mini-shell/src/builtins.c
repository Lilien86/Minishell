#include "minishell.h"

static int	is_flag_n(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (1);
	return (0);
}

void	ft_echo(t_token *tokens)
{
	int		newline;
	t_token	*current;

	newline = 1;  // By default, echo prints a newline at the end
	current = tokens->next;  // Skipping the "echo" token itself

	// Check if there is a '-n' flag to suppress the newline
	while (current && is_flag_n(current->value))
	{
		newline = 0;  // Do not print newline at the end
		current = current->next;
	}
	while (current != NULL)
	{
		ft_printf("%s", current->value);
		if (current->next != NULL)
			ft_printf(" ");  // Separate arguments with a space
		current = current->next;
	}

	if (newline)
		ft_printf("\n");  // Print the newline unless suppressed
}
