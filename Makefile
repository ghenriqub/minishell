# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 19:44:31 by lgertrud          #+#    #+#              #
#    Updated: 2025/07/10 16:52:43 by lgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror -lreadline -g

#directories
SRC_DIR = src
PARSER_DIR = src/parser
I_DIR = includes
LIBFT_DIR = libft

#includes
INCLUDES = -I$(I_DIR) -I$(LIBFT_DIR)

#libraries
LIBFT = $(LIBFT_DIR)/libft.a

#sources
SRC = $(PARSER_DIR)/main.c $(PARSER_DIR)/token.c $(PARSER_DIR)/utils.c $(PARSER_DIR)/token_utils.c

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
