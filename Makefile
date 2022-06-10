# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 11:51:21 by baubigna          #+#    #+#              #
#    Updated: 2022/06/09 18:03:25 by baubigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= srcs/main.c \
			srcs/args.c \
			srcs/builtins.c \
			srcs/cd.c \
			srcs/cleaning.c \
			srcs/commands.c \
			srcs/dollars_utils.c \
			srcs/echo.c \
			srcs/execute.c \
			srcs/fork.c \
			srcs/initialize.c \
			srcs/parse_utils.c \
			srcs/pipe_creation.c \
			srcs/print.c \
			srcs/quotes_dollars.c \
			srcs/quotes_utils.c \
			srcs/quotes.c \
			srcs/signals.c \
			srcs/token_check.c \
			srcs/token_creation.c \
			srcs/tokenize.c

OBJS	= ${SRCS:.c=.o}

GCC		= gcc #-fsanitize=address -g3

RM		= rm -rf

GFLAGS	= -Wall -Wextra -Werror

LIBFT    =   libft/libft.a

all:		 ${NAME}

.c.o:		
			${GCC} ${GFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	lib
			${GCC} ${GFLAGS} ${SRCS} ${LIBFT} -lreadline -o ${NAME}
lib:
			make -C libft

clean:
			${RM} ${OBJS}
			make -C libft clean

fclean:	clean
			${RM} ${NAME}
			${RM} $(LIBFT)

re:		fclean all

.PHONY:	all fclean clean re
