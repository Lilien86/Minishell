#include "../minishell.h"

int	check_numbers_arg_exit(char *endptr, t_token *current,
			t_minishell *shell)
{
	if (*endptr == '\0' && current->next)
	{
		print_error_and_set_status("minishell: exit: too many arguments\n",
			1, shell);
		return (0);
	}
	return (1);
}
