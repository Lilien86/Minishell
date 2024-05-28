#include "../minishell.h"

char	*read_line(char *delimiter)
{
	char	*line;

	line = readline(" > ");
	if (line == NULL)
	{
		if (line != NULL)
			free(line);
		ft_putstr_fd("bash: warning: here-document at line 1 delimited"
			"by end-of-file (wanted `%s')\n", 2);
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		if (line != NULL)
			free(line);
		return (NULL);
	}
	return (line);
}

char	*update_here_doc_content(char *line, char *here_doc_content)
{
	size_t	len;
	char	*temp;

	if (here_doc_content == NULL)
		here_doc_content = ft_strdup(line);
	else
	{
		len = ft_strlen(here_doc_content) + ft_strlen(line) + 2;
		temp = ft_calloc(len, 1);
		ft_strcpy(temp, here_doc_content);
		ft_strcat(temp, "\n");
		ft_strcat(temp, line);
		free(here_doc_content);
		here_doc_content = temp;
	}
	free(line);
	return (here_doc_content);
}