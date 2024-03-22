#include "../minishell.h"

void	merge_token_words(t_token *tokens)
{
	t_token *current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_WORD)
		{
			t_token *next_token = current->next;
			while (next_token != NULL && next_token->type == TOKEN_WORD)
			{
				size_t len1 = ft_strlen(current->value);
				size_t len2 = ft_strlen(next_token->value);
				char *new_value = (char *)malloc(len1 + len2 + 1);
				if (new_value == NULL)
				{
					ft_printf("Memory allocation failed\n");
					exit(EXIT_FAILURE);
				}
				ft_strcpy(new_value, current->value);
				ft_strcat(new_value, next_token->value);

				// Free the memory of next_token's value and update pointers
				 free(next_token->value);
				next_token->value = NULL;
				t_token *temp = next_token->next;
				free(next_token);
				next_token = temp;

				// Update the value of the current token
				free(current->value);
				current->value = new_value;
			}
			// Move to the next token
			current->next = next_token;
		}
		else
			current = current->next;
	}
}
