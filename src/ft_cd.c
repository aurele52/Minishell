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

int	ft_ispartenv(t_env	*varenv, char *str)
{
	return (ft_strcmp(varenv->name, str));
}

t_list	*ft_envvarexist(t_pos *envact, char *str)
{
	t_list	*varenv;
	int		i;

	i = 0;
	if (envact->start != 0)
	{
		varenv = envact->start;
		while (i <= *envact->size/* varenv != varenv->pos->start->back */)
		{
			if (!ft_ispartenv(varenv->content, str))
				return (varenv);
			varenv = varenv->next;
			i++;
		}
	}
	return (NULL);
}

void	ft_preaddvarenv(t_minishell *minishell, char *name, t_env *varenv)
{
	ft_addvarenv(minishell, name, varenv->value);
}

void	ft_updateenv(t_minishell *minishell, char *buff)
{
	t_list	*list;

	list = ft_envvarexist(minishell->actenv, "PWD");
	if (ft_envvarexist(minishell->actenv, "OLDPWD"))
		ft_lstdelone(ft_envvarexist(minishell->actenv, "OLDPWD"), 0);
	ft_preaddvarenv(minishell, "OLDPWD", list->content);
	if (ft_envvarexist(minishell->actenv, "PWD"))
		ft_lstdelone(ft_envvarexist(minishell->actenv, "PWD"), 0);
	ft_addvarenv(minishell, "PWD", buff);
}

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

int	ft_homechdir(t_env *varenv)
{
	if (!varenv)
		return (1);
	printf("HOME = %s\n", varenv->value);//
	if (chdir(varenv->value) == 0)
		return (0);
	else
		return (1);
}

int	ft_PWDcheck(t_minishell *minishell, t_command *command)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (!ft_envvarexist(minishell->actenv, "PWD"))
	{
		if (getcwd(buff, PATH_MAX))
			ft_addvarenv(minishell, "PWD", buff);
		else
		{
			(write(command->ofdout, "minishell: cd: could not get current working directory\n", ft_strlen("minishell: cd: could not get current working directory\n")));
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_minishell *minishell, t_command *command)
{
	t_list	*list;
	char	*buff;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	/*
		peut etre definir PATH_MAX dans le *.h
		*/
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (ft_doublstrlen(command->cmd) > 2)
	{
		write(command->ofdout, "minishell: cd: too many arguments\n", ft_strlen("minishell: cd: too many arguments\n"));
		return (1);
	}
	else if (ft_doublstrlen(command->cmd) == 2)
	{
		if (ft_PWDcheck(minishell, command))
			return (1);
		if (chdir(command->cmd[1]) == 0)
		{
			if (getcwd(buff, PATH_MAX))
				ft_updateenv(minishell, buff);
		}
		else
		{
			write (command->ofdout, "minishell: cd: ", ft_strlen("minishell: cd: "));
			write (command->ofdout, command->cmd[1], ft_strlen(command->cmd[1]));
			write (command->ofdout, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
			return (1);
		}
	}
	else if (ft_doublstrlen(command->cmd) == 1)
	{
		if (ft_PWDcheck(minishell, command))
			return (1);
		list = ft_envvarexist(minishell->actenv, "HOME");
		if (ft_homechdir(list->content) == 0)
		{
			if (getcwd(buff, PATH_MAX))
				ft_updateenv(minishell, buff);
		}
		else
		{
			write(command->ofdout, "minishell: cd: no home defined\n", ft_strlen("minishell: cd: no home defined\n"));
			return (1);
		}
	}
	return (0);
}