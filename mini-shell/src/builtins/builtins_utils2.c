#include "../minishell.h"

int	length_until_plus_equal(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '+')
		len++;
	return (len);
}

void remove_plus_char(char *str)
{
	char *plus_char;

	plus_char = ft_strchr(str, '+');
	if (plus_char)
		ft_memmove(plus_char, plus_char + 1, ft_strlen(plus_char));
}
// int update_existing_var(char *var, char ***env, int var_len, int *env_size) {
//     int i;
//     char *new_value;
//     char *new_env_entry;
//     int new_env_entry_len;

//     i = 0;
//     while (i < *env_size)
// 	{
//         if ((*env)[i] != NULL && ft_strncmp((*env)[i], var, (size_t)var_len) == 0 \
// 			&& ft_strchr((*env)[i], '='))
// 		{
// 			if (shell->is_plus_equal)
//             new_value = handle_plus_equal((*env)[i], var);
//             if (new_value == NULL)
//                 return (0);
//             new_env_entry_len = (int)(ft_strlen(var) - ft_strlen(ft_strchr(var, '+')) + ft_strlen(new_value) + 1);
//             new_env_entry = malloc((size_t)new_env_entry_len);
//             if (new_env_entry == NULL) 
// 			{
//                 free(new_value);
//                 return (0);
//             }
//             ft_strncpy(new_env_entry, var, ft_strlen(var) - ft_strlen(ft_strchr(var, '+')));
//             new_env_entry[ft_strlen(var) - ft_strlen(ft_strchr(var, '+'))] = '\0';
//             ft_strcat(new_env_entry, new_value);
//             free((*env)[i]);
//             (*env)[i] = new_env_entry;
//             free(new_value);
//             return (1);
//         }
//         i++;
//     }
//     return (0);
// }
