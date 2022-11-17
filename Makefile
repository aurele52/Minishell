# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/11/16 12:46:15 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

TESTER = tester

CC = gcc

FLAG = -g -Wall -Werror -Wextra 

SRC=	src/minishell/minishellinit.c	\
		src/minishell/ft_commandexec.c	\
		src/minishell/ft_getpath.c	\
		src/minishell/ft_tokenredirclean.c	\
		src/minishell/ft_heredoc.c	\
		src/minishell/ft_tokencmdclean.c	\
		src/minishell/ft_exit.c	\
		src/minishell/ft_token_create.c \
		src/minishell/ft_token_create2.c \
		src/minishell/ft_token_create3.c \
		src/minishell/ft_tokencheck.c \
		src/minishell/ft_error.c \
		src/minishell/ft_signal.c	\
		src/minishell/ft_posprint.c \
		src/env/env.c	\
		src/builtin/ft_echo.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_builtin.c	\
		src/builtin/ft_unset.c	\
		src/builtin/ft_export.c	\
		src/builtin/ft_pwd.c	\
		src/builtin/ft_env.c	\
		src/builtin/ft_preexit.c	\
		src/libft/ft_closevaria.c	\
		src/libft/ft_strjoin.c	\
		src/libft/ft_putnbrfd.c	\
		src/libft/ft_substr.c \
		src/libft/ft_setpos.c	\
		src/libft/ft_lstnew.c	\
		src/libft/ft_lstdelone.c	\
		src/libft/ft_malloc.c		\
		src/libft/ft_strlen.c	\
		src/libft/ft_strcmp.c	\
		src/libft/ft_posclear.c \
		src/libft/ft_strdup.c	\
		src/libft/ft_split.c \
		src/libft/ft_itoa.c	\
		src/libft/ft_atoi.c	\
		src/libft/ft_isalpha.c \
		src/libft/ft_isdigit.c \
		src/cast/castenv.c	\
		src/cast/castcommand.c	\
		src/cast/casttoken.c

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

norm:
	norminette

clean:
	rm -f $(OBJ) $(OBJ_MAIN)

fclean:	clean
	rm -f $(NAME)

re:	fclean all 


.PHONY: all clean fclean re	
