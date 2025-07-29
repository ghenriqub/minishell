# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 19:44:31 by lgertrud          #+#    #+#              #
#    Updated: 2025/07/28 14:17:19 by lgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror -lreadline -g

#directories
SRC_DIR = src
PARSER_DIR = src/parser
EXEC_DIR = src/execute
BUILTINS_DIR = src/builtins
I_DIR = includes
LIBFT_DIR = libft

#includes
INCLUDES = -I$(I_DIR) -I$(LIBFT_DIR)

#libraries
LIBFT = $(LIBFT_DIR)/libft.a

#sources
SRC = $(PARSER_DIR)/main.c \
		$(PARSER_DIR)/token.c \
		$(PARSER_DIR)/utils.c \
		$(PARSER_DIR)/token_utils.c \
		$(PARSER_DIR)/parser_to_builtins.c \
		$(PARSER_DIR)/get_environment_variable.c \
		$(PARSER_DIR)/blocks.c \
		$(PARSER_DIR)/heredoc.c \
	$(BUILTINS_DIR)/pwd.c \
		$(BUILTINS_DIR)/echo.c \
		$(BUILTINS_DIR)/env.c \
		$(BUILTINS_DIR)/exit.c \
		$(BUILTINS_DIR)/export.c \
		$(BUILTINS_DIR)/export_utils.c \
		$(BUILTINS_DIR)/unset.c \
		$(BUILTINS_DIR)/cd.c \
		$(BUILTINS_DIR)/cd_utils.c \
	$(EXEC_DIR)/minishell.c \
		$(EXEC_DIR)/path.c \
		$(EXEC_DIR)/redirections.c 

#objects
OBJS = $(SRC:.c=.o)

# Colors
YELLOW = \e[93m
GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

#Banners
INTRO = @echo "$(BLUE)🚀 Starting compilation of the $(YELLOW)Minishell$(RESET) $(BLUE)project by $(YELLOW)lgertrud$(RESET) $(BLUE)and $(YELLOW)ghenriqu$(RESET)...\n\
--------------------------------------------------------------"
END = @echo "\n$(GREEN)✔ Compilation complete!$(RESET)"

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(INTRO)
	@echo "$(YELLOW)[LOADING...]$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(END)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	@echo "$(YELLOW)[.o]$(RESET)Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:
	@echo "$(RED)[FCLEAN]$(RESET) Removing all generated files..."
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
