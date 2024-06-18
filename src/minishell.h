/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:00:35 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/18 12:02:19 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>

# define MAX_HISTORY_SIZE 100

# define READ_END 0
# define WRITE_END 1
# define MAX_PIPES 1024
# define FILENAME_LENGTH 10

extern int	g_exit_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_PIPE,
	TOKEN_DOUBLE_REDIRECT_OUT,
	TOKEN_HEREDOC,
}	t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	t_quote_type	quote_type;
	char			*value;
	struct s_token	*next;

}	t_token;

typedef struct s_pos_len
{
	int				pos;
	int				len;
	int				origin_len;
}	t_pos_len;

typedef struct s_file
{
	char			*name;
	int				fd;
	int				is_allocated;
}	t_file;

typedef struct s_redirect
{
	t_file		infile;
	t_file		outfile;
	char		**argv;
	int			pid;
}	t_redirect;

typedef struct s_coord
{
	int		i;
	int		j;
	int		replace_env;
}	t_coord;

typedef struct s_index_and_available_here_doc
{
	int		i;
	int		here_doc_available;
}	t_index_and_available_here_doc;

typedef struct s_minishell
{
	char		**env;
	t_token		*tokens;
	char		*input;
	t_redirect	*redirect_array;
	t_file		**tab_here_doc;
	int			nb_cmds;
	char		*history[MAX_HISTORY_SIZE];
	int			history_index;
	int			exit_status;
	int			is_single_quote;
	int			is_double_quote;
	int			last_var_ends_with_equal;
	int			is_plus_equal;
	int			env_size;
	int			syntax_error;
	int			pipes[MAX_PIPES][2];
	int			reset_exc;

}	t_minishell;

//TOKENIZATION
t_token		*init_token(t_token_type type, char *value, t_minishell *shell);
void		add_token(t_token **head, t_token *new_token);
t_token		*tokenize(const char *input, char **env, t_minishell *shell);
int			identify_double_char_tokens(const char **input,
				t_token **head, t_minishell *shell);
void		add_token_based_on_char(const char **input,
				t_token **head, char **env, t_minishell *shell);
int			handle_syntax_error(char **final_value,
				t_token **head, char quote_type, t_minishell *shell);

//TOKENIZATION_UTILS
int			is_special_char(char c);
char		*add_quoted_token(const char **input, t_token **head,
				char quote_type, t_minishell *shell);
void		add_word_token(const char **input, t_token **head, char **env,
				t_minishell *shell);
void		free_tokens(t_token **tokens);
void		identify_and_add_token(const char **input,
				t_token **head, char **env, t_minishell *shell);
void		handle_quotes(const char **input, t_token **head,
				t_minishell *shell, char **token_temp);
char		*process_quoted_content(const char *quoted_part,
				char quote_type, t_minishell *shell);
t_token		*init_token(t_token_type type, char *value, t_minishell *shell);

//SUBSTITUTE_ENV
int			var_length(const char *str, t_minishell *shell);
char		*copy_env_value(char *key, char **env, t_minishell *shell);
char		*substitute_var(const char *input, char **env, t_minishell *shell);
char		*append_char_to_str(char *str, char c);
char		*append_char_to_strfree(char *str, char c);
void		append_segment(char **final_value, char *segment);
char		*process_dollar(const char **input, char **env,
				char *result, t_minishell *shell);
char		*substitute_env_vars(const char *input,
				char **env, t_minishell *shell);
char		*substitute_env_vars_handle_quotes(char *word, char **env,
				t_minishell *shell);
char		*normalize_spaces(char *str);

//SIGNALS
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		init_signal_handlers(void);
void		handle_sigint_here_doc(int sig);
void		handle_nothing(int sig);
void		handle_sigint_without_prefix(int sig);
void		handle_sigquit_here_doc(int sig);
void		handle_sigquit_two(int sig);
void		handle_nothing_two(int sig);
void		handle_nothing_two(int sig);

//UTILS
char		*generate_random_filename(void);
void		free_redirect_array(t_minishell *shell, int size);

//READLINE
int			read_input(t_minishell *shell);
int			execute_builtins(int argc, char **argv, t_minishell *shell);
void		handle_input(t_minishell *shell);
void		free_history(char *history[MAX_HISTORY_SIZE]);
void		init_history(char *history[MAX_HISTORY_SIZE]);
void		process_input(t_minishell *shell);
int			execute_builtins_helper(t_token *arg_lst, t_minishell *shell);

//BUILTINS
void		ft_echo(t_token *tokens, int *exit_status, t_minishell *shell);
void		ft_pwd(t_token *arg_lst, int *exit_status);
void		ft_exit(t_token *tokens, t_minishell *shell);
void		ft_cd(t_token *tokens, char **env, int *exit_status);

//BUILTINS_ENV
void		ft_export(t_token *tokens, char ***env, int *exit_status,
				t_minishell *shell);
void		ft_unset(t_token *tokens, char ***env, int *exit_status);
void		ft_env(t_token *arg_lst, char **env, int *exit_status);
char		**add_new_env_var(char *var, char ***env, t_minishell *shell);
int			is_valid_var_name(const char *var, t_minishell *shell);
int			handle_export_token(t_token *token, char ***env,
				t_minishell *shell);
char		*handle_plus_equal(char *env_var, char *var);
int			length_until_plus_equal(const char *str);
int			update_existing_var(char *var, char ***env,
				int var_len, t_minishell *shell);
char		**create_new_env_array(char *var, char ***env,
				t_minishell *shell);
void		set_pwd_if_not_defined(char ***env);
void		increment_shlvl(char ***env);
void		update_env_with_pwd(char **env, char *new_pwd);
char		*create_new_pwd(void);

//EXIT_UTILS
int			check_numbers_arg_exit(char *endptr, t_token *current,
				t_minishell *shell);
void		print_error_and_set_status(char *msg, int status,
				t_minishell *shell);
int			strlen_without_space(const char *s);
int			check_length_and_sign(t_token *current, t_minishell *shell,
				int i_sign);
int			process_exit_arg(t_token *current, t_minishell *shell, int *i);
int			check_exit_arg_validity(t_token *current,
				t_minishell *shell, int *i);
void		close_fd_pipe(int pipes[MAX_PIPES][2]);

//BUILTINS_UTILS
int			is_flag_n(char *str);
char		*ft_getenv(const char *name, char **env);
void		print_env(char **env);
int			length_until_equal(const char *str);
int			process_export(t_token *tokens, char ***env, t_minishell *shell);
void		remove_plus_char(char *str);
char		*prepare_env_var(char *var);
void		environment_trail(char **env, int *exit_status);

//STRUCT_UTILS
t_minishell	*init_minishell(char **envp);
void		free_minishell(t_minishell *shell);
void		print_data(t_redirect *data_array, int nb_cmds);

//EXECUTION
void		fill_t_redirect(t_minishell *shell);
void		write_here_doc_in_file(char *content, int fd, t_minishell *shell);
char		*check_command_existence(char *cmd, char *env[]);
void		execute_command_shell(t_minishell *shell);
int			init_redirect_array(t_minishell *shell);
void		handle_input_output(t_minishell cpy,
				t_index_and_available_here_doc *index_and_available_here,
				t_minishell *shell, int *id_here_doc);
void		error_exit(char *message, t_minishell *shell);
void		handle_pipe(t_minishell *shell, int *i);
void		handle_output_redirect(t_minishell *cpy, t_token *current,
				int *i, t_minishell *shell);
void		handle_output_redirect_append(t_minishell *cpy, t_token *current,
				int *i, t_minishell *shell);
void		handle_input_redirect(t_minishell *cpy, t_token *current,
				int *i, t_minishell *shell);
void		handle_word(t_minishell *shell, t_token **current, int *i);
void		ft_exec(t_redirect *redirect_array, int index, t_minishell *shell,
				int pipes[MAX_PIPES][2]);
void		init_pipes(int pipes[MAX_PIPES][2]);
int			handle_wait(t_minishell *shell);
int			is_not_token_word(t_token *current);
void		handle_execute(t_minishell *shell, t_redirect *redirect_array,
				int index);

//HERE_DOC
t_file		here_doc(t_token *current, t_minishell *shell, int replace_env,
				t_file **tab_here_doc);
void		handle_here_doc(t_minishell *shell, t_file here_doc,
				char *delimiter, int replace_env);
void		choose_here_doc(t_minishell *shell, int *i, int id_here_doc);
t_file		**run_here_doc(t_minishell *shell);
char		*read_line(char *delimiter);
char		*update_here_doc_content(char *line, char *here_doc_content);
t_file		**fill_tab_here_doc(t_token *current, t_minishell *shell,
				t_file **tab_here_doc, int replace_env);
int			counter_here_doc(t_token *tokens);
t_list		*replace_env_variable(const char *content, t_pos_len *dollars,
				int num_vars, t_minishell *shell);
t_list		*fill_content_enough_variable_env(const char *content,
				t_pos_len *dollars, int num_vars);
char		*replace_content(t_list *list_content, t_list *list_vars);
void		remember_fd_here_doc(t_file *here_doc, t_minishell *shell);
void		handle_fork_error(t_minishell *shell);
void		handle_parent_process(pid_t pid, t_minishell *shell);

//OPEN_FILE
void		open_file_in(t_file *file, int index, t_minishell *shell);
void		open_file_out(t_file *file, t_minishell *cpy, int index,
				t_minishell *shell);
void		open_file_out_append(t_file *file, t_minishell *cpy, int index,
				t_minishell *shell);
//UTILS_CHECK
int			check_redirect_in_to_pipe(t_token *tokens);
int			check_builtins(char *cmd);
int			is_token_redirection(t_token *token);
t_token		*convert_argv_to_list(int argc, char **argv);
int			counter_cmds(t_token *tokens);
int			check_valid_redirect(t_token *token);

//UTILS_FDS
int			open_file_and_handle_errors(t_minishell *shell,
				t_file here_doc_cpy);
char		*get_variable_path(char **env);
int			file_exist_in_directory(char *path, char *file);
int			is_valid_fd(int fd);

//UTILS TO EXEC
const char	*here_doc_replace_var_env(const char *content, t_minishell *shell);
int			counter_dollars(const char *content);
int			len_to_dollars(const char *content, int index);
void		print_list(t_list *list);
int			is_file(const char *path);
int			check_file_in_directory(DIR *dir, char *path, char *file);

//FREE
void		free_tab_here_doc(t_file **tab_here_doc, int nb_cmds);

#endif
