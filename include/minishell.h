/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:37:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 16:00:38 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED   "\x1B[31m"
# define GREEN   "\x1B[32m"
# define YELLOW   "\x1B[33m"
# define BLUE   "\x1B[34m"
# define MAGENTA   "\x1B[35m"
# define CYAN   "\x1B[36m"
# define WHITE   "\x1B[37m"
# define RESET "\x1B[0m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pos
{
	struct s_list	*start;
	int				*size;
}	t_pos;

enum e_type
{
	NOTZEROONMYMINISHELL,
	SPACES,
	WORD,
	DOUBLECOTE,
	SINGLECOTE,
	PARENTHESIS
};

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*back;
	void			*content;
	struct s_pos	*pos;
}	t_list;

typedef struct s_minishell
{
	t_pos		*garbage;
	t_pos		*garbagecmd;
	char		**env;
	char		**envact;
	char		**argv;
	int			argc;
	char		*prompt;
	char		*error;
	t_pos		*tokenlist;
}	t_minishell;

typedef struct s_token
{
	char	*tokenstr;
	int		tokentype;
}	t_token;

typedef struct s_command
{
	int		fdin;
	int		fdout;
	char	**cmd;
}	t_command;

/* liste */

t_pos	*ft_setpos(t_pos *free);
void	ft_lstdelone(t_list *lst, int freee);
t_list	*ft_lstnew(void *content, t_pos *pos, t_pos *free);
void	ft_posclear(t_pos *pos, int freee);

/* libft */

char	*ft_strjoin(char *s1, char *s2, t_pos *garbage);
void	ft_putnbrfd(int n, int fd);
void	ft_printtoken(void *ptr);
void	ft_posprint(t_pos *pos, void (*fct)(void *));
char	*ft_strdup(const char *s, t_pos *garbage);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_pos *garb);
int		ft_strcmp(const char *str1, const char *str2);
void	*ft_malloc(int size, t_pos *free);
int		ft_exit(t_minishell *minishell, char *str);
size_t	ft_strlen(const char *s);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

/* minishell */
char	*readline(const char *prompt);
void	ft_tokencreate(t_minishell *minishell, char *str);
void	ft_error(t_minishell *minishell, char *str);

#endif
