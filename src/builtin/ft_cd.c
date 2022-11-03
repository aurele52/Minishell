/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:14:02 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/26 18:14:30 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addvarenv(t_minishell *minishell, char *name, char *value)
{
	t_env	*line;

	line = ft_malloc(sizeof(*line), minishell->garbage);
	if (!line)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(line, minishell->actenv, minishell->garbage);
	if (!minishell->actenv->start->back)
		ft_exit(minishell, "malloc error\n");
	line->name = name;
	line->lname = ft_strlen(line->name);
	line->value = value;
	line->lvalue = ft_strlen(line->value);
}

int	ft_ispartenv(t_env	*varenv, char *str)
{
	return (ft_strcmp(varenv->name, str));
}

void	ft_preaddvarenv(t_minishell *minishell, char *name, t_env *varenv)
{
	ft_addvarenv(minishell, name, varenv->value);
}

void	ft_updateenv(t_minishell *minishell, char *buff)
{
	t_list	*list;

	list = ft_envlist(minishell, "PWD");
	if (ft_envlist(minishell, "OLDPWD"))
		ft_lstdelone(ft_envlist(minishell, "OLDPWD"), 0);
	ft_preaddvarenv(minishell, "OLDPWD", list->content);
	if (ft_envlist(minishell, "PWD"))
		ft_lstdelone(ft_envlist(minishell, "PWD"), 0);
	ft_addvarenv(minishell, "PWD", buff);
}

int	ft_homechdir(t_env *varenv)
{
	if (!varenv)
		return (1);
	if (chdir(varenv->value) == 0)
		return (0);
	else
		return (1);
}

int	ft_PWDcheck(t_minishell *minishell)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (!ft_envlist(minishell, "PWD"))
	{
		if (getcwd(buff, PATH_MAX))
			ft_addvarenv(minishell, "PWD", buff);
		else
		{
			ft_error(minishell, "minishell: cd: could not get current working directory\n");
			return (1);
		}
	}
	return (0);
}

void	ft_cd(t_minishell *minishell, t_command *command)
{
	t_list	*list;
	char	*buff;
	char	*str;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (ft_strlen(command->cmd[0]) > 2)
		ft_error(minishell, "minishell: cd: too many arguments\n");
	else if (ft_strlen(command->cmd[0]) == 2)
	{
		if (ft_PWDcheck(minishell))
			return ;
		if (chdir(command->cmd[1]) == 0)
		{
			if (getcwd(buff, PATH_MAX))
			{
				if (!ft_strcmp(command->cmd[1], "//"))
					ft_updateenv(minishell, "//");
				else
					ft_updateenv(minishell, buff);
				minishell->laststatus = 0;
			}
		}
		else
		{
			str = ft_strdup("minishell: cd: ", minishell->garbagecmd);
			str = ft_strjoin(str, command->cmd[1], minishell->garbagecmd);
			str = ft_strjoin(str, ft_strdup(": No such file or directory\n", minishell->garbagecmd), minishell->garbagecmd);
			if (!str)
				ft_exit(minishell, "malloc error\n");
			ft_error(minishell, str);
			return ;
		}
	}
	else if (ft_strlen(command->cmd[0]) == 1)
	{
		if (ft_PWDcheck(minishell))
			return ;
		list = ft_envlist(minishell, "HOME");
		if (ft_homechdir(list->content) == 0)
		{
			if (getcwd(buff, PATH_MAX))
				ft_updateenv(minishell, buff);
			minishell->laststatus = 0;
		}
		else
		{
			ft_error(minishell, "minishell: cd: no home defined\n");
			return ;
		}
	}
	return ;
}
