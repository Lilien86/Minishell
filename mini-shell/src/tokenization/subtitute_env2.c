/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitute_env2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:31 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/04 11:46:33 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_dollar(const char **input, char **env, char *result,
		t_minishell *shell)
{
	char	*temp;
	int		var_len;
	char	*new_result;

	temp = substitute_var(*input, env, shell);
	new_result = malloc(ft_strlen(result) + ft_strlen(temp) + 1);
	if (!new_result)
		return (NULL);
	ft_strcpy(new_result, result);
	ft_strcat(new_result, temp);
	free(temp);
	var_len = var_length(*input + 1, shell) + 1;
	*input += var_len;
	return (new_result);
}

char	*substitute_env_vars(const char *input, char **env, t_minishell *shell)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*input)
	{
		if (shell->is_single_quote != 1 && *input == '$'
			&& (ft_isalnum(*(input + 1)) \
			|| *(input + 1) == '_' || *(input + 1) == '?'))
			temp = process_dollar(&input, env, result, shell);
		else
			temp = append_char_to_str(result, *input++);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		if (result)
			free(result);
		result = temp;
	}
	return (result);
}

int	check_forbidden_characters(char **word, char *result, t_minishell *shell)
{
	char	*error_msg;

	error_msg = NULL;
	if (**word == '(' || **word == ')')
		error_msg = "syntax error: parenthesis are not allowed\n";
	else if (ft_strncmp(*word, "&&", 2) == 0)
		error_msg = "syntax error: logical operators '&&' are not allowed\n";
	else if (ft_strncmp(*word, "||", 2) == 0)
		error_msg = "syntax error: logical operators '||' are not allowed\n";
	else if (**word == '*')
		error_msg = "syntax error: wildcard '*' is not allowed\n";
	if (error_msg)
	{
		ft_putstr_fd(error_msg, 2);
		shell->syntax_error = 1;
		shell->exit_status = 2;
		free(result);
		return (1);
	}
	return (0);
}

static char	*process_word(char *word, char **env,
				char *result, t_minishell *shell)
{
	char	*temp;

	while (*word)
	{
		if (check_forbidden_characters(&word, result, shell))
			return (NULL);
		if (shell->is_single_quote != 1 && *word == '$'
			&& (ft_isalnum(*(word + 1)) || *(word + 1) == '_'
				|| *(word + 1) == '?'))
			temp = process_dollar((const char **)&word, env, result, shell);
		else
			temp = append_char_to_str(result, *word++);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		free(result);
		result = temp;
	}
	return (result);
}

char	*substitute_env_vars_handle_quotes(char *word, char **env,
			t_minishell *shell)
{
	char	*result;
	char	*final_result;
	char	*normalized_result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	final_result = process_word(word, env, result, shell);
	if (final_result == NULL)
		return (NULL);
	if (!shell->is_double_quote)
	{
		normalized_result = normalize_spaces(final_result);
		free(final_result);
		final_result = normalized_result;
	}
	word = ft_strdup(final_result);
	free(final_result);
	return (word);
}
