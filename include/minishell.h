/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:37:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 01:24:10 by audreyer         ###   ########.fr       */
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

# include <stdarg.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>  

typedef struct s_pos
{
	struct s_list	*start;
	int				*size;
}	t_pos;

enum e_type
{
	NOTZEROONMYMINISHELL,
	SINGLEQUOTE,
	WORD,
	DOLLAR,
	DOUBLEQUOTE,
	HEREDOC,
	WRITE,
	APPEND,
	IN,
	SPACES,
	NL,
	ERROR,
	OR,
	AND,
	PIPE,
	PARENTHESIS,
	HEREDOCEXT,
	CMD
};

typedef struct s_env
{
	char	*name;
	char	*value;
	size_t	lname;
	size_t	lvalue;
}	t_env;

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
	t_pos		*actenv;
	char		**argv;
	int			argc;
	int			*pipe;
	char		*prompt;
	char		*error;
	t_pos		*tokenlist;
}	t_minishell;

typedef struct s_token
{
	char	*str;
	int		type;
}	t_token;

typedef struct s_command
{
	char	*fdin;
	char	*fdout;
	int		ofdout;
	int		ofdin;
	char	*error;
	char	*heredoc;
	char	**cmd;
	int		type;
}	t_command;

/* liste */

t_pos		*ft_setpos(t_pos *free);
void		ft_lstdelone(t_list *lst, int freee);
t_list		*ft_lstnew(void *content, t_pos *pos, t_pos *free);
void		ft_posclear(t_pos *pos, int freee);

/* libft */

int			ft_closevaria(int i, ...);
char		*ft_strjoin(char *s1, char *s2, t_pos *garbage);
void		ft_putnbrfd(int n, int fd);
void		ft_printtoken(t_minishell *minishell, void *ptr);
void		ft_posprint(t_minishell *minishell, t_pos *pos, void (*fct)(t_minishell *, void *));
char		*ft_strdup(const char *s, t_pos *garbage);
char		*ft_substr(char const *s, unsigned int start, size_t len, t_pos *garb);
int			ft_strcmp(const char *str1, const char *str2);
void		*ft_malloc(int size, t_pos *free);
int			ft_exit(t_minishell *minishell, char *str);
size_t		ft_strlen(const char *s);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
char		*ft_unsplit(char **tab, char *charset, t_pos *garbage);

/* minishell */

char		**ft_split(char const *s, char c, t_pos *free);
void		ft_child(t_minishell *minishell, t_list *tokenlist);
char		*ft_getcmdfile(t_minishell *minishell, t_command *command);
int			ft_type(t_list *tokenlist);
char		*ft_str(t_list *tokenlist);
void		ft_tokenredirclean(t_minishell *minishell);
void		ft_tokencmdclean(t_minishell *minishell);
void		ft_parsetoken(t_minishell *minishell);
void		ft_tokencreate(t_minishell *minishell, char *str);
void		ft_error(t_minishell *minishell, char *str);
void		ft_leaf(t_minishell *minishell);
void		ft_createleaf(t_minishell *minishell);
void		ft_parseleaf(t_minishell *minishell);
char		*ft_readline(char *str, t_pos *garbage);
t_minishell	*ft_minishellinit(int argc, char **argv, char **env);
void		ft_expanddoublequote(t_token *token);
void		ft_expanddollar(t_token *token);
void	ft_printenv(t_minishell	*minishell, void *ptr);

/* builtin */

void		ft_echo(t_command *command);
void		ft_fillofdout(t_command *command, unsigned int i);
int			ft_nonewline(char *str);

#endif
