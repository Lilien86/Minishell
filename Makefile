# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lauger <lauger@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 11:15:18 by lauger            #+#    #+#              #
#    Updated: 2024/03/15 08:38:47 by lauger           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./minishell

LIBFT = ./libft
LIBFT_LIBRARY = $(LIBFT)/libft.a

CC = /bin/cc
CFLAGS = -g -Wextra -Werror -Wall -I $(LIBFT)
LDFLAGS = -L $(LIBFT) -lft

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SRC =

OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT_LIBRARY) $(OBJ)
	@echo "$(YELLOW)Compiling source files...$(NC)"
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation is complete. Generated executable: $(NAME).$(NC)"

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling file $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@/bin/make --quiet -C $(LIBFT) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaning complete.$(NC)"

fclean: clean
	@echo "$(YELLOW)Removing executable $(NAME)...$(NC)"
	@/bin/make --quiet -C $(LIBFT) fclean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Removal complete.$(NC)"

re: fclean all

.PHONY: all clean fclean re
