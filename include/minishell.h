/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:37:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/01 12:58:44 by audreyer         ###   ########.fr       */
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
# define BUFFER_SIZE	2000

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
# include <linux/limits.h>
# include <limits.h>
# include <signal.h>

typedef struct sigaction	t_sigaction;

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
	int			heredoc;
	char		**env;
	t_pos		*actenv;
	char		**argv;
	int			argc;
	int			*pipe;
	char		*prompt;
	char		*error;
	t_pos		*tokenlist;
	int			laststatus;
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
	char	**cmd;
	char	*file;
	int		type;
}	t_command;

/* liste */

t_pos		*ft_setpos(t_pos *garbage);
void		ft_lstdelone(t_list *lst, int garbage);
t_list		*ft_lstnew(void *content, t_pos *pos, t_pos *garbage);
void		ft_posclear(t_pos *pos, int garbage);
void		ft_posprint(t_minishell *minishell, t_pos *pos, void (*fct)(t_minishell *, void *, int), int fd);

/* libft */

int			ft_closevaria(int i, ...);
char		*ft_strjoin(char *s1, char *s2, t_pos *garbage);
void		ft_putnbrfd(int n, int fd);
char		*ft_strdup(const char *s, t_pos *garbage);
char		*ft_substr(char const *s, int start, int len, t_pos *garb);
int			ft_strcmp(const char *str1, const char *str2);
void		*ft_malloc(int size, t_pos *garbage);
int			ft_strlen(const char *s);
char		**ft_split(char const *s, char c, t_pos *garbage);
char		*ft_itoa(int n, t_pos *garbage);
int			ft_atoi(char *str);

/* minishell */

void		ft_heredocclean(t_minishell *minishell);
void		ft_child(t_minishell *minishell, t_list *tokenlist);
void		ft_tokenredirclean(t_minishell *minishell);
void		ft_tokencmdclean(t_minishell *minishell);
void		ft_parsetoken(t_minishell *minishell);
int			ft_tokencreate(t_minishell *minishell, char *str);
void		ft_leaf(t_minishell *minishell);
void		ft_createleaf(t_minishell *minishell);
void		ft_parseleaf(t_minishell *minishell);
char		*ft_readline(char *str, t_pos *garbage);

/*bazar*/

void		ft_printtoken(t_minishell *minishell, void *ptr, int fd);
int			ft_exit(t_minishell *minishell, char *str);
char		*ft_getcmdfile(t_minishell *minishell, t_command *command);
void		ft_error(t_minishell *minishell, char *str);
t_minishell	*ft_minishellinit(char **env);
char		*ft_expanddoublequote(t_minishell *minishell, char *str);
char		*ft_expanddollar(t_minishell *minishell, char *str);
void		ft_printenv(t_minishell	*minishell, void *ptr, int fd);
int			ft_errorstr(char *str);
void		ft_signal(int sig, siginfo_t *siginfo, void *ucontext);


/*env*/

char		*ft_searchinenv(t_minishell *minishell, char *str);
t_list		*ft_envlist(t_minishell *minishell, char *str);

/* builtin */

int			ft_isbuiltin(t_command *command);
void		ft_preexit(t_minishell *minishell, t_command *command);
void		ft_env(t_minishell *minishell, t_command *command);
void		ft_unset(t_minishell *minishell, t_command *command);
void		ft_pwd(t_minishell *minishell, t_command *command);
void		ft_export(t_minishell *minishell, t_command *command);
void		ft_builtin(t_minishell *minishell, t_command *command);
void		ft_echo(t_command *command);
void		ft_cd(t_minishell *minishell, t_command *command);

/*cast*/

t_command	*ft_commandget(t_list *tokenlist);
char		*ft_value(t_env *env);
char		*ft_name(t_env *env);
int			ft_type(t_list *tokenlist);
char		*ft_str(t_list *tokenlist);
int			ft_fdin(t_list *tokenlist);
int			ft_ofdin(t_list *tokenlist);
int			ft_ofdout(t_list *tokenlist);
int			ft_fdout(t_list *tokenlist);

#endif
