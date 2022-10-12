/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:37:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/12 13:36:02 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pos
{
	struct s_list	*start;
	struct s_list	*end;
	int				*size;
}	t_pos;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*back;
	int				*content;
	struct s_pos	*pos;
}	t_list;

typedef struct s_minishell
{
	t_pos		*garbage;
	char		**env;
	char		**argv;
	int			argc;
	char		*error;
}	t_minishell;

/* liste */
t_pos				*ft_setpos(t_pos *free);
void				ft_lstdelone(t_list *lst, int freee);
t_list				*ft_lstnew(void *content, t_pos *pos, t_pos *free);
void				ft_posclear(t_pos *pos, int freee);

/* libft */

int					ft_strcmp(const char *str1, const char *str2);
void				*ft_malloc(int size, t_pos *free);
int					ft_exit(t_pos *garbage, char *str);
size_t				ft_strlen(const char *s);

/* minishell */

char				*readline(const char *prompt);

#endif
