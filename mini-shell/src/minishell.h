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

typedef enum e_token_type
{
	TOKEN_WORD,// 0
	TOKEN_REDIRECT_IN,// 1 <
	TOKEN_REDIRECT_OUT,// 2 >
	TOKEN_PIPE,// 3 |
	TOKEN_DOUBLE_REDIRECT_OUT,// 4 >>
	TOKEN_HEREDOC,// 5 <<
	TOKEN_SPACE,// 6
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

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
	int			nb_cmds;
	char		*history[MAX_HISTORY_SIZE];
	int			history_index;
	int			exit_status;

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
void		handle_sigint_here_doc(int sig/*, void *shell*/);

//UTILS
char		*generate_random_filename(void);
int			is_token_redirection(t_token *token);
void		free_redirect_array(t_minishell *shell, int size);

//READLINE
int			read_input(t_minishell *shell);
void		execute_command(t_minishell *shell);
void		handle_input(t_minishell *shell);
void		free_history(char *history[MAX_HISTORY_SIZE]);
void		init_history(char *history[MAX_HISTORY_SIZE]);
void		process_input(t_minishell *shell);

//BUILTINS
void		ft_echo(t_token *tokens, int *exit_status);
void		ft_cd(t_token *tokens, char **env, int *exit_status);
void		ft_pwd(int *exit_status);

//BUILTINS_ENV
void		ft_export(t_token *tokens, char ***env, int *exit_status);
void		ft_unset(t_token *tokens, char ***env, int *exit_status);
void		ft_env(char **env, int *exit_status);
char		**add_new_env_var(char *var, char ***env, int *env_size);

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

//EXECUTION
void	fill_t_redirect(t_minishell *shell);
void	here_doc(t_token *current, t_minishell *shell, int i);
void	handle_here_doc(t_minishell *shell, int i, char *delimiter);
void	write_here_doc_in_file(char *content, int fd);
void	execute_redirection(t_minishell *shell);
char	*check_command_existence(const char *cmd, char *env[]);

void	handle_pipe(t_minishell *shell, int *i);
void	handle_heredoc(t_minishell *shell, t_token *current, int *i);
void	handle_output_redirect(t_minishell *shell,
	t_token *current, int *i, int is_double_redirect);
void	handle_input_redirect(t_minishell *shell, t_token *current, int *i);
void	check_file(t_file *file, int is_append, t_minishell *shell);
void	handle_word(t_minishell *shell, t_token **current, int *i);

#endif
