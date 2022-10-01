# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/08/02 19:25:35 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAG = -g -Wall -Werror -Wextra 

SRC=	src/minishell.c

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -I include -c $< -o $(<:.c=.o)

INC = include/minishell.h

INC_LIBFT = include/libft.h

LIB = libft.a

all:	$(LIB) $(NAME)

$(NAME):	$(OBJ) $(INC) $(INC_LIBFT)
	$(CC) $(FLAG) $(OBJ) $(LIB) -o $(NAME)

clean:
	rm -f $(OBJ) libft.a

fclean:	clean
	rm -f $(NAME)

$(LIB)	:
	make -C ./libft/
	rm -f libft.a
	cp libft/libft.a .

re			: fclean all 

git:
	make git -C ./libft/
	rm -f libft.a
	make fclean
	git add obj
	git add src
	git add Makefile
	git add include/
	read S; git commit -m $${S}
	git push

fini:
	rm libft
	cp -r ../libft .
	rm -rf libft/.git
	make fclean -C ./libft/
	git add libft
	make git

.PHONY: all clean fclean re libft
