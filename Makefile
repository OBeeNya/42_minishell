# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 11:51:21 by baubigna          #+#    #+#              #
#    Updated: 2022/04/28 14:39:01 by baubigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= srcs/main.c \
			srcs/builtins.c \
			srcs/files.c \
			srcs/initialize.c \
			srcs/parse_utils.c \
			srcs/paths.c \
			srcs/signals.c \
			srcs/tokenize.c

OBJS	= ${SRCS:.c=.o}

GCC		= gcc

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
