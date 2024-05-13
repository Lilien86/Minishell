#include "../minishell.h"

t_list *fill_content_enouth_variable_env(const char *content, t_pos_len *dollars, int num_vars)
{
    int i;
    t_list *list;
    int start;

    i = 0;
    list = NULL;
    start = 0;
    while (i < num_vars)
    {
        if (dollars[i].pos > start)
        {
            char *sub;
            sub = ft_substr(content, (unsigned int)start, (size_t)(dollars[i].pos) - (size_t)start);
            ft_lstadd_back(&list, ft_lstnew(sub));
        }
        start = dollars[i].pos + dollars[i].len;
        i++;
    }
    if ((size_t)start < ft_strlen(content))
    {
        char *sub;
        sub = ft_substr(content, (unsigned int)start, (size_t)ft_strlen(content) - (size_t)start);
        ft_lstadd_back(&list, ft_lstnew(sub));
    }
    print_list(list);
    return (list);
}

const char  *here_doc_replace_var_env(const char *content)
{
    t_pos_len   *dollars;
    int     j;
    int     i;

    i = 0;
    j = 0;
    dollars = ft_calloc((size_t)counter_dollars(content), sizeof(t_pos_len));
    if (dollars == NULL)
        return (content);
    while(content[i] != '\0')
    {
        if (content[i] == '$')
        {
            dollars[j].pos = i;
            dollars[j].len = len_to_dollars((const char *)content, i);
            j++;
        }
        i++;
    }
    print_pos_dollars(dollars, j);
    fill_content_enouth_variable_env(content, dollars, counter_dollars(content));
    return (content);
    
}