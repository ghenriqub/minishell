# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 19:44:31 by lgertrud          #+#    #+#              #
#    Updated: 2025/08/16 14:46:00 by lgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_BONUS = minishell_bonus

#compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAG = -lreadline

#directories
SRC_DIR = src
PARSER_DIR = src/parser
EXEC_DIR = src/execute
BUILTINS_DIR = src/builtins
BONUS_DIR = src_bonus
PAR_BONUS_DIR = src_bonus/parser_bonus
BUI_BONUS_DIR = src_bonus/builtins_bonus
EXE_BONUS_DIR = src_bonus/execute_bonus
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
		$(PARSER_DIR)/blocks_utils.c \
		$(PARSER_DIR)/heredoc.c \
	$(BUILTINS_DIR)/pwd.c \
		$(BUILTINS_DIR)/echo.c \
		$(BUILTINS_DIR)/env.c \
		$(BUILTINS_DIR)/exit.c \
		$(BUILTINS_DIR)/exit_utils.c \
		$(BUILTINS_DIR)/export.c \
		$(BUILTINS_DIR)/export_utils.c \
		$(BUILTINS_DIR)/unset.c \
		$(BUILTINS_DIR)/cd.c \
		$(BUILTINS_DIR)/cd_utils.c \
	$(EXEC_DIR)/minishell.c \
		$(EXEC_DIR)/path.c \
		$(EXEC_DIR)/redirections.c \
		$(EXEC_DIR)/simple_command.c \
		$(EXEC_DIR)/pipe.c

SRC_BONUS = $(PAR_BONUS_DIR)/main_bonus.c \
		$(PAR_BONUS_DIR)/token_bonus.c \
		$(PAR_BONUS_DIR)/utils_bonus.c \
		$(PAR_BONUS_DIR)/token_utils_bonus.c \
		$(PAR_BONUS_DIR)/parser_to_builtins_bonus.c \
		$(PAR_BONUS_DIR)/get_environment_variable_bonus.c \
		$(PAR_BONUS_DIR)/blocks_bonus.c \
		$(PAR_BONUS_DIR)/blocks_utils_bonus.c \
		$(PAR_BONUS_DIR)/heredoc_bonus.c \
		$(PAR_BONUS_DIR)/and_or_bonus.c \
		$(PAR_BONUS_DIR)/and_or_utils_bonus.c \
	$(BUI_BONUS_DIR)/pwd_bonus.c \
		$(BUI_BONUS_DIR)/echo_bonus.c \
		$(BUI_BONUS_DIR)/env_bonus.c \
		$(BUI_BONUS_DIR)/exit_bonus.c \
		$(BUI_BONUS_DIR)/exit_utils_bonus.c \
		$(BUI_BONUS_DIR)/export_bonus.c \
		$(BUI_BONUS_DIR)/export_utils_bonus.c \
		$(BUI_BONUS_DIR)/unset_bonus.c \
		$(BUI_BONUS_DIR)/cd_bonus.c \
		$(BUI_BONUS_DIR)/cd_utils_bonus.c \
	$(EXE_BONUS_DIR)/minishell_bonus.c \
		$(EXE_BONUS_DIR)/path_bonus.c \
		$(EXE_BONUS_DIR)/redirections_bonus.c \
		$(EXE_BONUS_DIR)/simple_command_bonus.c \
		$(EXE_BONUS_DIR)/pipe_bonus.c


#objects
OBJS = $(SRC:.c=.o)

#objects bonus
OBJSB = $(SRC_BONUS:.c=.o)

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
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAG) -o $(NAME)

bonus: $(LIBFT) $(NAME_BONUS)

$(NAME_BONUS): $(OBJSB)
	@echo "$(GREEN)[OK]$(RESET) BONUS!!"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJSB) $(LIBFT) $(LDFLAG) -o $(NAME_BONUS)

%.o: %.c
	@echo "$(YELLOW)[.o]$(RESET)Compiling $<..."
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@rm -f $(OBJS) $(OBJSB)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:
	@echo "$(RED)[FCLEAN]$(RESET) Removing all generated files..."
	@rm -f $(NAME) $(NAME_BONUS) $(OBJS) $(OBJSB)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
