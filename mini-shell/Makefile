NAME = ./minishell

LIBFT = ./libft
LIBFT_LIBRARY = $(LIBFT)/libft.a

CC = /bin/cc
CFLAGS = -g -Wextra -Werror -Wall -Wconversion -Wunreachable-code -Wunused-function -I $(LIBFT)

LDFLAGS = -L $(LIBFT) -lft -lreadline

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SRC = src/main.c src/struct_util.c \
src/tokenization/tokenization.c src/tokenization/tokenization_utils.c \
src/tokenization/tokenization_utils2.c \
src/tokenization/subtitute_env.c  src/tokenization/subtitute_env2.c \
src/readline/add-readline.c src/readline/readline-history.c \
src/signal/handle_signal.c \
src/builtins/builtins.c src/builtins/builtins_utils.c \
src/builtins/exit.c src/builtins/cd.c \
src/builtins/env/ft_export.c src/builtins/env/builtins_env.c \
src/builtins/env/ft_export2.c \
src/execution/here_doc.c src/execution/generate_random_name.c \
src/execution/fill_t_redirect.c src/execution/handle_symbol_redirect.c \
src/execution/fill_args.c src/execution/while_here_doc.c \
src/execution/free_t_redirect.c src/execution/execute.c \
src/execution/search_path_cmd.c

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
