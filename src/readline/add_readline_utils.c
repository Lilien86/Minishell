/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_readline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:53:02 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/18 11:45:28 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_read(t_minishell *shell)
{
	if (!shell)
		return ;
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens != NULL)
	{
		free_tokens(&(shell->tokens));
		shell->tokens = NULL;
	}
	if (shell->redirect_array != NULL)
	{
		if (shell->nb_cmds == 0)
			shell->nb_cmds++;
		free_redirect_array(shell, shell->nb_cmds);
		shell->redirect_array = NULL;
	}
	if (shell->tab_here_doc != NULL)
	{
		free_tab_here_doc(shell->tab_here_doc, shell->nb_cmds);
		shell->tab_here_doc = NULL;
	}
	close_fd_pipe(shell->pipes);
}

int	read_input(t_minishell *shell)
{
	int	local_exit_status;

	while (1)
	{
		if (shell->input != NULL)
		{
			free(shell->input);
			shell->input = NULL;
		}
		signal(SIGQUIT, handle_nothing_two);
		shell->input = readline("minishell > ");
		if (shell->input == NULL || ft_strcmp(shell->input, "exit") == 0)
		{
			if (g_exit_signal != 0)
				local_exit_status = g_exit_signal;
			else
				local_exit_status = shell->exit_status;
			free_minishell(shell);
			ft_printf("exit\n");
			exit(local_exit_status);
		}
		handle_input(shell);
		free_read(shell);
	}
	return (0);
}

void	handle_input(t_minishell *shell)
{
	if (ft_strcmp(shell->input, "") == 0)
		return ;
	process_input(shell);
}

int	execute_builtins_helper(t_token *arg_lst, t_minishell *shell)
{
	if (ft_strcmp(arg_lst->value, "echo") == 0)
		ft_echo(arg_lst, &shell->exit_status, shell);
	else if (ft_strcmp(arg_lst->value, "cd") == 0)
		ft_cd(arg_lst, shell->env, &shell->exit_status);
	else if (ft_strcmp(arg_lst->value, "pwd") == 0)
		ft_pwd(arg_lst, &shell->exit_status);
	else if (ft_strcmp(arg_lst->value, "export") == 0)
		ft_export(arg_lst, &(shell->env), &shell->exit_status, shell);
	else if (ft_strcmp(arg_lst->value, "unset") == 0)
		ft_unset(arg_lst, &shell->env, &shell->exit_status);
	else if (ft_strcmp(arg_lst->value, "env") == 0
		&& arg_lst->value[3] == '\0')
		ft_env(arg_lst, shell->env, &shell->exit_status);
	else if (ft_strcmp(arg_lst->value, "exit") == 0)
		ft_exit(arg_lst, shell);
	else
		return (0);
	return (1);
}
