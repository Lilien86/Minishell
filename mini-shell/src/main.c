#include "minishell.h"

int	main(void)
{
	t_token	*tokens;

	tokens = read_input();
	free_tokens(&tokens);

	return (0);
}
