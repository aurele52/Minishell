/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:58:58 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/28 18:08:06 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	newenv = ft_setpos(minishell->garbage);
	if (!newenv)
		ft_exit(minishell, "malloc error\n");
	i = 0;
	while (minishell->env[i])
	{
		line = ft_malloc(sizeof(*line), minishell->garbage);
		if (!line)
			ft_exit(minishell, "malloc error\n");
		ft_lstnew(line, newenv, minishell->garbage);
		if (!newenv->start->back)
			ft_exit(minishell, "malloc error\n");
		line->name = ft_strdup(ft_split(minishell->env[i],
					'=', minishell->garbage)[0], minishell->garbage);
		line->lname = ft_strlen(line->name);
		line->value = ft_substr(minishell->env[i], line->lname + 1,
				ft_strlen(minishell->env[i]), minishell->garbage);
		line->lvalue = ft_strlen(line->value);
		i++;
	}
	return (newenv);
}

void	ft_minishellinit2(t_minishell *minishell)
{
	minishell->heredoc = 0;
	minishell->heredocprompt = 0;
	minishell->laststatus = 0;
	minishell->error = 0;
	minishell->garbagecmd = ft_setpos(0);
	if (minishell->garbagecmd == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->pipe = ft_pipeinit(minishell);
}

t_minishell	*ft_minishellinit(char **env)
{
	t_minishell	*minishell;
	t_pos		*garbage;

	garbage = ft_setpos(0);
	minishell = ft_malloc(sizeof(*minishell), garbage);
	if (minishell == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->garbage = garbage;
	ft_minishellinit2(minishell);
	minishell->fdutil = dup(0);
	minishell->env = env;
	minishell->actenv = ft_envinit(minishell);
	if (!minishell->actenv)
		ft_exit(minishell, "malloc error\n");
	minishell->tokenlist = ft_setpos(minishell->garbage);
	if (!minishell->tokenlist)
		ft_exit(minishell, "malloc error\n");
	return (minishell);
}

void	ft_minishell(t_minishell *minishell)
{
	char	*str;

	while (1)
	{
		str = ft_minishell2(minishell);
		if (!str)
			continue ;
		add_history(str);
		if (ft_tokencreate(minishell, str) == 0
			|| *minishell->tokenlist->size != 0)
		{
			ft_tokenredirclean(minishell);
			if (*minishell->tokenlist->size != 0)
			{
				ft_heredocclean(minishell);
				if (g_heredoc != 130)
				{
					ft_tokencmdclean(minishell);
					ft_child(minishell, minishell->tokenlist->start);
				}
			}
			ft_error(minishell, ft_itoa(minishell->laststatus,
					minishell->garbage));
		}
	}
}
