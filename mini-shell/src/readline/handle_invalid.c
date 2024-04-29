// #include "../minishell.h"

// int execute_external_command(t_minishell *shell)
// {
// 	char *cmd_path;

// 	cmd_path = check_command_existence(shell->tokens->value, shell->env);
// 	if (!cmd_path) {
// 		if (errno == ENOENT) {
// 			ft_putstr_fd(" No such file or directory\n", 2);
// 			shell->exit_status = 127;
// 		} else if (errno == EACCES) {
// 			ft_putstr_fd(" Permission denied\n", 2);
// 			shell->exit_status = 126;
// 		} else {
// 			ft_putstr_fd(" command not found\n", 2);
// 			shell->exit_status = 127;
// 		}
// 		return 0;
// 	}
// 	//execute_command_by_path(cmd_path, shell);
// 	free(cmd_path);
// 	return 1;
// }