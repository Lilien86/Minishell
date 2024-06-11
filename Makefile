NAME = ./minishell

LIBFT = ./libft
LIBFT_LIBRARY = $(LIBFT)/libft.a

CC = /bin/cc

CFLAGS = -Wextra -Werror -Wall -I $(LIBFT)

LDFLAGS = -L $(LIBFT) -lft -lreadline

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SRC = src/main.c src/shell_struct/struct_utils.c \
src/shell_struct/free_utils.c\
src/tokenization/tokenization.c src/tokenization/tokenization_utils.c \
src/tokenization/subtitute_env.c  src/tokenization/env_variable_handling.c \
src/tokenization/subtitute_env_utils.c \
src/tokenization/quotes_handle.c src/tokenization/quotes_processing.c \
src/tokenization/quotes_handle_utils.c \
src/readline/add_readline.c src/readline/readline_history.c \
src/readline/add_readline_utils.c \
src/signal/handle_signal.c \
src/builtins/builtins.c src/builtins/builtins_utils.c src/builtins/builtins_utils2.c\
src/builtins/exit.c src/builtins/exit_utils.c src/builtins/cd.c \
src/builtins/env/env_utils.c \
src/builtins/env/ft_export.c src/builtins/env/builtins_env.c \
src/builtins/env/ft_export_utils.c src/execution/here_doc/generate_random_name.c \
src/execution/fill_t_redirect.c src/execution/handle_symbol_redirect.c \
src/execution/process_t_redirect.c \
src/execution/fill_args.c src/execution/here_doc/fill_fd_heredoc.c \
src/execution/error_exit.c \
src/execution/free_t_redirect.c \
src/execution/search_path_cmd.c src/execution/execute.c \
src/readline/utils_check.c src/execution/here_doc/exec_here_doc.c \
src/readline/utils_fd.c src/execution/here_doc/fill_struct_here_doc.c src/execution/here_doc/fill_struct_tab_here_doc.c \
src/execution/utils_to_exec.c src/execution/utils_to_exec2.c \
src/execution/here_doc/replace_env_variable_here_doc.c src/execution/open_file.c \
src/execution/execute_final.c src/execution/here_doc/join_content_heredoc_with_variable.c \
src/execution/here_doc/replace_content_var_in_heredoc.c src/tokenization/init_token.c

OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT_LIBRARY):
	/bin/make --quiet -C $(LIBFT)

$(NAME): $(LIBFT_LIBRARY) $(OBJ)
	@echo
	@echo "$(YELLOW)Compiling source files...$(NC)"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation is complete. Generated executable: $(NAME).$(NC)"
	@echo

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling file $<...$(NC)"
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

clean:
	@echo
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@/bin/make --quiet -C $(LIBFT) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaning complete.$(NC)"
	@echo

fclean: clean
	@echo
	@echo "$(YELLOW)Removing executable $(NAME)...$(NC)"
	@/bin/make --quiet -C $(LIBFT) fclean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Removal complete.$(NC)"
	@echo

re: fclean all

.PHONY: all clean fclean re
