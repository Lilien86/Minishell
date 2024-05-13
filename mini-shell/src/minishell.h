#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAX_HISTORY_SIZE 100

#define READ_END 0
#define WRITE_END 1
#define MAX_PIPES 512

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_PIPE,
	TOKEN_DOUBLE_REDIRECT_OUT,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	int				is_double_quotes;
}	t_token;

typedef struct s_pos_len
{
	int             pos;
	int				len;
}	t_pos_len;

typedef struct s_file
{
	char			*name;
	int				fd;
}	t_file;

typedef struct s_redirect
{
	t_file		infile;
	t_file		outfile;
	char		**argv;
}	t_redirect;

//PARSING
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
	int			space_flag;
	int			last_var_ends_with_equal;

}	t_minishell;

//TOKENIZATION
t_token		*init_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_token);
t_token		*tokenize(const char *input, char **env, t_minishell *shell);
void		identify_double_char_tokens(const char **input, t_token **head);
void		add_token_based_on_char(const char **input,
				t_token **head, char **env, t_minishell *shell);

//TOKENIZATION_UTILS
int			is_special_char(char c);
void		add_quoted_token(const char **input, t_token **head,
				char quote_type, t_minishell *shell);
void		add_word_token(const char **input, t_token **head, char **env,
				t_minishell *shell);
void		free_tokens(t_token **tokens);

//TOKENIZATION_UTILS2
void		identify_and_add_token(const char **input,
				t_token **head, char **env, t_minishell *shell);
void		check_space_after_token(const char **input, t_token**head,
				t_minishell *shell);
void		handle_quotes(const char **input, t_token **head,
				t_minishell *shell, const char **start);
char		*process_quoted_content(const char *quoted_part,
				char quote_type, t_minishell *shell);

//SUBSTITUTE_ENV
int			var_length(const char *str, t_minishell *shell);
char		*copy_env_value(char *key, char **env, t_minishell *shell);
char		*substitute_var(const char *input, char **env, t_minishell *shell);
char		*append_char_to_str(char *str, char c);
char		*process_single_quote(const char **input,
				char *result, t_minishell *shell);

//SUBSTITUTE_ENV2
char		*process_dollar(const char **input, char **env,
				char *result, t_minishell *shell);
char		*substitute_env_vars(const char *input,
				char **env, t_minishell *shell);

//SIGNALS
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		init_signal_handlers(void);
void		handle_sigint_here_doc(int sig);

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

//HANDLE_INVALID
int			execute_external_command(t_minishell *shell);

//BUILTINS
void		ft_echo(t_token *tokens, int *exit_status, t_minishell *shell);
void		ft_pwd(int *exit_status);
void		ft_exit(t_token *tokens, t_minishell *shell);
void		ft_cd(t_token *tokens, char **env, int *exit_status);

//BUILTINS_ENV
void		ft_export(t_token *tokens, char ***env, int *exit_status,
				t_minishell *shell);
void		ft_unset(t_token *tokens, char ***env, int *exit_status);
void		ft_env(char **env, int *exit_status);
char		**add_new_env_var(char *var, char ***env, int *env_size);
int			is_valid_var_name(const char *var);
int			handle_export_token(t_token *token, char ***env, int *env_size,
				t_minishell *shell);
int			is_valid_var_value(const char *value);

//BUILTINS_UTILS
int			is_flag_n(char *str);
char		*ft_getenv(const char *name, char **env);
void		print_env(char **env);
int			length_until_equal(const char *str);
int			process_export(t_token *tokens, char ***env, int *env_size);
void		print_argv(char **argv);

//STRUCT_UTILS
t_minishell	*init_minishell(char **envp);
void		free_minishell(t_minishell *shell);
void		print_data(t_redirect *data_array, int nb_cmds);
char		**convert_linked_list_to_array(t_token *head);

//EXECUTION
void		fill_t_redirect(t_minishell *shell);
void		write_here_doc_in_file(char *content, int fd, t_minishell *shell);
char		*check_command_existence(const char *cmd, char *env[]);
void		execute_command_shell(t_minishell *shell);

void		error_exit(char *message, t_minishell *shell);
void		handle_pipe(t_minishell *shell, int *i);
void		handle_output_redirect(t_minishell *cpy, t_token *current,
				int *i, int is_double_redirect, t_minishell *shell);
void		handle_input_redirect(t_minishell *cpy, t_token *current,
				int *i, t_minishell *shell);
void		check_file(t_file *file, int is_append, t_minishell *shell,
				int status);
void		handle_word(t_minishell *shell, t_token **current, int *i);

//------here_doc
t_file		here_doc(t_token *current, t_minishell *shell);
void		handle_here_doc(t_minishell *shell, t_file here_doc,
				char *delimiter);
void		to_choice_here_doc(t_minishell *shell, int *i);
void		run_here_doc(t_minishell *shell);

//UTILS_CHECK
int			check_redirect_in_to_pipe(t_token *tokens);
int			check_builtins(char *cmd);
int			is_token_redirection(t_token *token);
t_token		*convert_argv_to_list(int argc, char **argv);
void		print_linked_list(t_token *head);
int			counter_cmds(t_token *tokens);

//UTILS_FDS
int			open_file_and_handle_errors(t_minishell *shell, t_file here_doc_cpy);

//UTILS TO EXEC
const char  *here_doc_replace_var_env(const char *content);
void   		print_pos_dollars(t_pos_len *dollars, int size);
int  		counter_dollars(const   char *content);
int  		len_to_dollars(const char *content, int index);
void		print_list(t_list *list);


#endif
