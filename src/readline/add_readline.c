/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:52:11 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/11 10:19:16 by ybarbot          ###   ########.fr       */
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
	if (shell->redirect_array[0].argv == NULL)
		return ;
	if (check_builtins(shell->redirect_array[0].argv[0]) == 1)
	{
		execute_builtins(ft_strlen_map(shell->redirect_array->argv),
			shell->redirect_array->argv, shell);
	}
	else
	{
		shell->redirect_array->argv[0] = check_command_existence(
				shell->redirect_array[0].argv[0], shell->env);
		if (shell->redirect_array->argv[0] == NULL)
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

	if (!argv || !argv[0])
		return (1);
	arg_lst = convert_argv_to_list(argc, argv);
	if (ft_strncmp(arg_lst->value, "echo", 4) == 0)
		ft_echo(arg_lst, &shell->exit_status, shell);
	else if (ft_strncmp(arg_lst->value, "cd", 2) == 0)
		ft_cd(arg_lst, shell->env, &shell->exit_status);
	else if (ft_strncmp(arg_lst->value, "pwd", 3) == 0)
		ft_pwd(arg_lst, &shell->exit_status);
	else if (ft_strncmp(arg_lst->value, "export", 6) == 0)
		ft_export(arg_lst, &(shell->env), &shell->exit_status, shell);
	else if (ft_strncmp(arg_lst->value, "unset", 5) == 0)
		ft_unset(arg_lst, &shell->env, &shell->exit_status);
	else if (ft_strncmp(arg_lst->value, "env", 3) == 0
		&& arg_lst->value[3] == '\0')
		ft_env(arg_lst, shell->env, &shell->exit_status);
	else if (ft_strncmp(arg_lst->value, "exit", 4) == 0)
		ft_exit(arg_lst, shell);
	free_tokens(&arg_lst);
	return (1);
}
