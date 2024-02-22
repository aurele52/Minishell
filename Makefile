# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/12/15 13:18:56 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE=	minishell/minishellinit.c	\
		minishell/minishellinit2.c	\
		minishell/ft_commandexec.c	\
		minishell/ft_commandexec2.c	\
		minishell/ft_commandexec3.c	\
		minishell/ft_getpath.c	\
		minishell/ft_tokenredirclean.c	\
		minishell/ft_tokenredirclean2.c	\
		minishell/ft_signal.c	\
		minishell/ft_heredoc.c	\
		minishell/ft_tokencmdclean.c	\
		minishell/ft_tokencmdclean2.c	\
		minishell/ft_tokencmdclean3.c	\
		minishell/ft_tokencmdclean4.c	\
		minishell/ft_exit.c	\
		minishell/ft_token_create.c \
		minishell/ft_token_create2.c \
		minishell/ft_token_create3.c \
		minishell/ft_token_create4.c \
		minishell/ft_tokencheck.c \
		minishell/ft_error.c \
		minishell/ft_posprint.c \
		env/env.c	\
		builtin/ft_echo.c \
		builtin/ft_cd.c \
		builtin/ft_cd2.c \
		builtin/ft_cd3.c \
		builtin/ft_builtin.c	\
		builtin/ft_unset.c	\
		builtin/ft_export.c	\
		builtin/ft_export2.c	\
		builtin/ft_pwd.c	\
		builtin/ft_env.c	\
		builtin/ft_preexit.c	\
		libft/ft_closevaria.c	\
		libft/ft_strjoin.c	\
		libft/ft_putnbrfd.c	\
		libft/ft_substr.c \
		libft/ft_setpos.c	\
		libft/ft_lstnew.c	\
		libft/ft_lstdelone.c	\
		libft/ft_malloc.c		\
		libft/ft_strlen.c	\
		libft/ft_strcmp.c	\
		libft/ft_posclear.c \
		libft/ft_strdup.c	\
		libft/ft_split.c \
		libft/ft_itoa.c	\
		libft/ft_atoi.c	\
		libft/ft_isalpha.c \
		libft/ft_isdigit.c \
		cast/castenv.c	\
		cast/castcommand.c	\
		cast/casttoken.c	\
		main.c

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ			=	$(SRC:.c=.o)

DOBJ		=	${SRC:.c=.d}

NAME		=	minishell

INC			=	include/minishell.h

CC			=	cc

FLAGS		=	-g -Wall -Werror -Wextra -MMD

RM			=	rm -f

all:		$(NAME)

-include ${DOBJ}
.c.o:
			$(CC) $(FLAGS) -I include -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ) $(INC)
			$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
			${RM} $(OBJ) ${DOBJ}

fclean:		clean
			${RM} $(NAME)

re:			fclean all 

.PHONY:		all clean fclean re .c.o
