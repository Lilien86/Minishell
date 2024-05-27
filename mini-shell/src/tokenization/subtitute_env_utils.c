#include "../minishell.h"

char	*append_char_to_strfree(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}
