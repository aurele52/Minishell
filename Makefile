# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/10/18 00:13:42 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

TESTER = tester

CC = gcc

FLAG = -g -fsanitize=address -Wall -Werror -Wextra 

SRC=	src/minishell.c	\
		src/ft_tokenredirclean.c	\
		src/ft_tokencmdclean.c	\
		src/ft_closevaria.c	\
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
		src/ft_split.c \
		src/ft_echo.c

SRC_MAIN=	src/main.c

SRC_MAIN_TEST=	src/main_test.c

OBJ = $(SRC:.c=.o)

OBJ_MAIN = $(SRC_MAIN:.c=.o)

OBJ_MAIN_TEST = $(SRC_MAIN_TEST:.c=.o)

.c.o:
	$(CC) $(FLAG) -I include -lreadline -c $< -o $(<:.c=.o)

INC = include/minishell.h


all:	$(NAME)

$(TESTER):	$(OBJ) $(OBJ_MAIN_TEST) $(INC)
	$(CC) $(FLAG) $(OBJ) $(OBJ_MAIN_TEST) -lreadline -o $(TESTER)
	rm -f ./tester/tester
	mv $(TESTER) ./tester/$(TESTER)
	@make -C ./tester

$(NAME):	$(OBJ) $(INC) $(OBJ_MAIN)
	$(CC) $(FLAG) $(OBJ) $(OBJ_MAIN) -lreadline -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_MAIN)

fclean:	clean
	rm -f $(NAME)

re:	fclean all 


.PHONY: all clean fclean re	
