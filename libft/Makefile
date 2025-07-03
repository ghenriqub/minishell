# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 14:55:02 by lgertrud          #+#    #+#              #
#    Updated: 2025/05/21 18:15:39 by lgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_SRCS = ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
             ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
             ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
             ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
             ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
             ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
             ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c ft_swap.c ft_sort_int_tab.c \
			 get_next_line_utils.c get_next_line.c

PRINTF_SRCS =	ft_printf/ft_printf.c ft_printf/ft_iputchar_fd.c ft_printf/ft_iputnbr_base.c \
				ft_printf/ft_iputstr_fd.c ft_printf/ft_print_pointer.c ft_printf/functions.c

OBJS = $(LIBFT_SRCS:.c=.o) $(PRINTF_SRCS:.c=.o)

HEADERS = -I.

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
