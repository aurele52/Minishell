/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:04:18 by audreyer          #+#    #+#             */
/*   Updated: 2022/08/08 15:54:09 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# define BUFFER_SIZE 2000
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

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

int	ft_strcmp(const char *s1, const char *s2);
int		**ft_splitint(char *c, t_pos *free);
void	ft_exit(t_pos *garbage, char *str);
int		ft_abs(int a);
char	*get_next_line(int fd, t_pos *free);
int		ft_voidtoint(int *i);
void	*ft_mallocint(int i, t_pos *free);
void	*ft_malloc(int size, t_pos *free);
t_list	*ft_lstmin(t_pos *pos);
int		ft_lstrange(t_list *list);
t_list	*ft_lstmax(t_pos *pos);
t_list	*ft_lstmedian(t_pos *pos);
char	*ft_unsplit(char **tab, char *charset, t_pos *free);
void	ft_setintzerovaria(int i, ...);
void	ft_putnbr(int nb);
void	ft_posprint(t_pos *pos);
t_list	*ft_lstnew(void *content, t_pos *pos, t_pos *free);
t_pos	*ft_setpos(t_pos *free);
void	*ft_freevaria(int i, ...);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_posclear(t_pos *pos, int freee);
void	ft_lstdelone(t_list *lst, int freee);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char));
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int character);
int		ft_isalpha(int character);
int		ft_isalnum(int character);
int		ft_isascii(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strdup(const char *s, t_pos *free);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strstr(const char *big, const char *little);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_memset(void *b, int c, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_pos *free);
char	*ft_strjoin(char *s1, char *s2, t_pos *free);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c, t_pos *split);

#endif
