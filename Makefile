# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 11:51:21 by baubigna          #+#    #+#              #
#    Updated: 2022/05/24 15:29:41 by baubigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= srcs/main.c \
			srcs/builtins.c \
			srcs/cleaning.c \
			srcs/dollars_utils.c \
			srcs/execute.c \
			srcs/initialize.c \
			srcs/parse_utils.c \
			srcs/quotes.c \
			srcs/signals.c \
			srcs/token_creation.c \
			srcs/tokenize.c \
			srcs/quotes_dollars.c \
			srcs/quotes_utils.c

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
