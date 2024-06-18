/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:52:11 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 14:47:27 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		ft_printf("Type de Token: %d, quote: %d, Valeur: %s\n",
			current->type, current->quote_type, current->value);
		current = current->next;
	}
}

static void	execute_command_logic(t_minishell *shell)
{
	init_pipes(shell->pipes);
	if (shell->redirect_array[0].argv == NULL)
		return ;
	if (check_builtins(shell->redirect_array[0].argv[0]) == 1)
	{
		if (shell->exit_status != 2)
			execute_builtins(ft_strlen_map(shell->redirect_array->argv),
				shell->redirect_array->argv, shell);
	}
	else
	{
		if (shell->redirect_array->argv[0] == NULL
			|| ft_strcmp(shell->redirect_array->argv[0], "") == 0)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			shell->exit_status = 127;
			return ;
		}
		if (shell->exit_status != 2)
			execute_command_shell(shell);
	}
}

static void	execute_input_commands(t_minishell *shell)
{
	if (is_token_redirection(shell->tokens) == 0)
	{
		fill_t_redirect(shell);
		execute_command_logic(shell);
	}
	else
	{
		fill_t_redirect(shell);
		execute_command_shell(shell);
	}
}

void	process_input(t_minishell *shell)
{
	add_history(shell->input);
	if (shell->history[shell->history_index] != NULL)
		free(shell->history[shell->history_index]);
	shell->history[shell->history_index] = ft_strdup(shell->input);
	shell->history_index = (shell->history_index + 1) % MAX_HISTORY_SIZE;
	shell->tokens = tokenize(shell->input, shell->env, shell);
	execute_input_commands(shell);
}

int	execute_builtins(int argc, char **argv, t_minishell *shell)
{
	t_token	*arg_lst;
	int		result;

	if (!argv || !argv[0])
		return (1);
	arg_lst = convert_argv_to_list(argc, argv);
	result = execute_builtins_helper(arg_lst, shell);
	if (!result)
	{
		printf("minishell: %s: command not found\n", arg_lst->value);
		free_tokens(&arg_lst);
		return (0);
	}
	free_tokens(&arg_lst);
	return (1);
}
