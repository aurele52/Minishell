# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/10/13 11:38:21 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAG = -g -Wall -Werror -Wextra 

SRC=	src/minishell.c	\
		src/ft_strjoin.c	\
		src/ft_putnbrfd.c	\
		src/ft_posprint.c \
		src/ft_substr.c \
		src/ft_setpos.c	\
		src/ft_lstnew.c	\
		src/ft_exit.c	\
		src/ft_lstdelone.c	\
		src/ft_malloc.c		\
		src/ft_strlen.c	\
		src/ft_strcmp.c	\
		src/ft_posclear.c \
		src/ft_token_create.c \
		src/ft_isalpha.c \
		src/ft_strdup.c	\
		src/ft_isalnum.c \
		src/ft_error.c \
		src/ft_leaf.c

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -I include -lreadline -c $< -o $(<:.c=.o)

INC = include/minishell.h


all:	$(NAME)

$(NAME):	$(OBJ) $(INC)
	$(CC) $(FLAG) $(OBJ) -lreadline -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re			: fclean all 

#read S; git commit -m $${S}

.PHONY: all clean fclean re
