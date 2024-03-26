#include "minishell.h"

int	main(void)
{
	read_input();
	return (0);
}

// #include "../minishell.h"

// // Assurez-vous que cette fonction est déclarée dans minishell.h si vous souhaitez l'utiliser à l'extérieur de ce fichier.

// void	debug_print_tokens(t_token *tokens) {
//     t_token *current = tokens;
//     ft_printf("Début de l'affichage des tokens:\n");
//     while (current != NULL) {
//         ft_printf("Type de Token: %d, Valeur: %s\n", current->type, current->value);
//         current = current->next;
//     }
//     ft_printf("Fin de l'affichage des tokens.\n");
// }
