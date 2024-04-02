#include "../minishell.h"

static void print_env(char **env)
{
    int i = 0;
    while (env[i]) {
        ft_printf("declare -x %s\n", env[i]);
        i++;
    }
}

static int length_until_equal(const char *str)
{
    int len = 0;
    while (str[len] != '\0' && str[len] != '=') {
        len++;
    }
    return len;
}

static void add_new_env_var(char *var, char ***env, int *env_size)
{
    int i = 0;
    int var_len = length_until_equal(var);
    while (i < *env_size) {
        if ((*env)[i] != NULL && ft_strncmp((*env)[i], var, (size_t)var_len) == 0 && (*env)[i][var_len] == '=') {
            free((*env)[i]);
            (*env)[i] = ft_strdup(var);
            return;
        }
        i++;
    }

    size_t old_size = sizeof(char *) * (size_t)(*env_size);
    size_t new_size = sizeof(char *) * ((size_t)(*env_size) + 2);

    char **new_env = (char **)ft_realloc(*env, new_size, old_size);
    if (!new_env) {
        return;
    }

    new_env[*env_size] = ft_strdup(var);
    if (!new_env[*env_size]) {
        return;
    }

    new_env[*env_size + 1] = NULL; 
    *env = new_env;
    (*env_size)++;
}


void ft_export(t_token *tokens, char ***env) {
    int env_size;

    env_size = 0;
    while ((*env)[env_size])
		env_size++;
    if (!tokens->next) {
        print_env(*env);
        return;
    }
    tokens = tokens->next;
    while (tokens) {
        add_new_env_var(tokens->value, env, &env_size);
        tokens = tokens->next;
    }
}
