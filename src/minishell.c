/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <audreyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:27:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 01:26:32 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*ft_pipeinit(t_minishell *minishell)
{
	int	*i;

	i = ft_malloc(sizeof(int) * 3, minishell->garbage);
	if (!i)
		ft_exit(minishell, "malloc error\n");
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (i);
}

t_pos	*ft_envinit(t_minishell *minishell)
{
	t_pos	*newenv;
	t_env	*line;
	size_t	i;

	newenv = ft_setpos(minishell->garbagecmd);
	if (!newenv)
		ft_exit(minishell, "malloc error\n");
	i = 0;
	while (minishell->env[i])
	{
		line = ft_malloc(sizeof(*line), minishell->garbagecmd);
		if (!line)
			ft_exit(minishell, "malloc error\n");
		ft_lstnew(line, newenv, minishell->garbage);
		if (!newenv->start->back)
			ft_exit(minishell, "malloc error\n");
		line->name = ft_strdup(ft_split(minishell->env[i], '=', minishell->garbage)[0], minishell->garbage);
		line->lname = ft_strlen(line->name);
		line->value = ft_substr(minishell->env[i], line->lname + 1, ft_strlen(minishell->env[i]), minishell->garbage);
		line->lvalue = ft_strlen(line->value);
		i++;
	}
	return(newenv);
}

t_minishell	*ft_minishellinit(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_pos		*garbage;

	garbage = ft_setpos(0);
	minishell = ft_malloc(sizeof(*minishell), garbage);
	if (minishell == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->garbage = garbage;
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->garbagecmd = ft_setpos(0);
	if (minishell->garbagecmd == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->env = env;
	minishell->actenv = ft_envinit(minishell);
	if (!minishell->actenv)
		ft_exit(minishell, "malloc error\n");
	minishell->pipe = ft_pipeinit(minishell);
	minishell->error = 0;
	minishell->prompt = ft_strjoin(ft_strjoin(
				ft_strdup("\x1b[32m", garbage), ft_strdup(argv[0], garbage),
				garbage), ft_strdup("\x1b[0m ", garbage), garbage);
	if (minishell->prompt == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->tokenlist = ft_setpos(minishell->garbage);
	if (!minishell->tokenlist)
		ft_exit(minishell, "malloc error\n");
	return (minishell);
}

void	ft_setcolor(char *color)
{
	write(1, color, ft_strlen(color));
}

void	ft_resetcolor(void)
{
	const char	*color = RESET;

	write(1, color, ft_strlen(color));
}

char	*ft_readline(char *prompt, t_pos *garbage)
{
	char	*str;

	str = readline(prompt);
	ft_lstnew(str, garbage, 0);
	if (garbage->start->back == 0)
		return (0);
	return (str);
}
