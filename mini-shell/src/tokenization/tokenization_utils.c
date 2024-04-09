#include "../minishell.h"

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void add_quoted_token(const char **input, t_token **head, char quote_type, char **env)
{
    const char *start = *input;
    (*input)++;
    size_t len = 0;
    while ((*input)[len] && (*input)[len] != quote_type)
        len++;
    if ((*input)[len] == quote_type) {
        char *quoted_part = ft_strndup(start + 1, len);  // +1 to skip the opening quote
        char *value = quote_type == '"' ? substitute_env_vars(quoted_part, env) : ft_strdup(quoted_part);
        add_token(head, init_token(TOKEN_WORD, value));
        free(quoted_part);
        free(value);
        *input += len;
    } else {
        ft_printf("minishell: syntax error: missing quotes\n");
        free_tokens(head);
    }
}


void add_word_token(const char **input, t_token **head, char **env)
{
    const char *start;
	char *word;
	size_t len;
	char *substituted_value;

	start = *input;
    while (**input && !ft_isspace(**input) && !is_special_char(**input))
		(*input)++;
	
	len = (size_t)(*input - start); 
    if (len > 0)
	{
        word = ft_strndup(start, len);
        substituted_value = substitute_env_vars(word, env);
        add_token(head, init_token(TOKEN_WORD, substituted_value));
        free(word);
        free(substituted_value);
    }
    if (**input)
        (*input)--;
}


void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void identify_and_add_token(const char **input, t_token **head, char **env)
{
    if (**input == '\'' || **input == '"') {
        add_quoted_token(input, head, **input, env);  // Pass env here
    } else if (is_special_char(**input)) {
        add_token_based_on_char(input, head, env);
    } else if (!ft_isspace(**input)) {
        add_word_token(input, head, env);  // Pass env here
    }
}
