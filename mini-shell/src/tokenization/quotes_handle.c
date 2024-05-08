#include "../minishell.h"

static size_t find_quote_end(const char *input, char quote_type)
{
    size_t len = 0;

    while (input[len] && input[len] != quote_type)
	{
        len++;
	}
    return len;
}

char	*process_quoted_content(const char *quoted_part,
					char quote_type, t_minishell *shell)
{
	char	*value;

	if (quote_type == '"')
		value = substitute_env_vars(quoted_part, shell->env, shell);
	else
		value = ft_strdup(quoted_part);
	return (value);
}

static char *process_quoted_segment(const char *start, size_t len, char quote_type, t_minishell *shell)
{
    char *segment;
    char *processed_segment;

    segment = ft_strndup(start, len);
    if (!segment)
        return NULL;
    processed_segment = process_quoted_content(segment, quote_type, shell);
    free(segment);
    return processed_segment;
}

static void append_segment(char **final_value, char *segment)
{
    char *temp;
	if (!segment)
		return;
    temp = ft_strjoin(*final_value, segment);
	if (temp)
	{
    	//free(*final_value);
    	*final_value = temp;
	}
}

char  *add_quoted_token(const char **input, t_token **head, char quote_type, t_minishell *shell)
{
    const char *start;
    size_t len;
    char *final_value;
    char *segment;
	//const char *temp;

    final_value = ft_strdup("");
    while (**input == quote_type) {
        (*input)++;
        start = *input;
        len = find_quote_end(*input, quote_type);
        if ((*input)[len] != quote_type) {
            ft_printf("minishell: syntax error: missing closing quote '%c'\n", quote_type);
            free(final_value);
            free_tokens(head);
            return (NULL);
        }
        segment = process_quoted_segment(start, len, quote_type, shell);
        if (!segment) {
            free(final_value);
            return (NULL);
        }
        append_segment(&final_value, segment);
        free(segment);
        *input += len + 1;
    }
	// if (!ft_isspace(**input) && !is_special_char(**input) && **input != '\0' && **input != quote_type)
	// {
	// 	temp = *input;
	// 	while (!ft_isspace(**input) && !is_special_char(**input) && **input != '\0' && **input != quote_type)
	// 		(*input)++;
	// 	segment = ft_strndup(temp, (size_t)(*input - temp));
	// 	if (segment)
	// 	{
	// 		append_segment(&final_value, segment);
	// 		free(segment);
	// 	}
	// }
    // if (final_value[0] != '\0')
    //     add_token(head, init_token(TOKEN_WORD, final_value));
    return(final_value);
}

