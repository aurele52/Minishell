/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:14:02 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/29 12:37:30 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_homechdir(t_env *varenv)
{
	if (!varenv)
		return (1);
	if (chdir(varenv->value) == 0)
		return (0);
	else
		return (1);
}

int	ft_pwdcheck(t_minishell *minishell)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (getcwd(buff, PATH_MAX))
		ft_updatepwd(minishell, buff);
	return (0);
}

void	ft_elseif(t_minishell *minishell, t_command *command, char *buff)
{
	char	*str;

	ft_pwdcheck(minishell);
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
		str = ft_strdup("minishell: cd: ", minishell->garbage);
		str = ft_strjoin(str, command->cmd[1], minishell->garbage);
		str = ft_strjoin(str, ft_strdup(": No such file or directory\n",
					minishell->garbage), minishell->garbage);
		if (!str)
			ft_exit(minishell, "malloc error\n");
		ft_error(minishell, str);
		return ;
	}
}

void	ft_elseif2(t_minishell *minishell, char *buff)
{
	t_list	*list;

	ft_pwdcheck(minishell);
	list = ft_envvarexist(minishell->actenv, "HOME");
	if (!list)
	{
		ft_error(minishell, "minishell: cd: HOME not set\n");
		return ;
	}
	else if (ft_homechdir(list->content) == 0)
	{
		if (getcwd(buff, PATH_MAX))
			ft_updateenv(minishell, buff);
		minishell->laststatus = 0;
	}
	else
	{
		ft_error(minishell, "minishell: cd: HOME not set\n");
		return ;
	}
}

void	ft_cd(t_minishell *minishell, t_command *command)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (ft_doublstrlen(command->cmd) > 2)
		ft_error(minishell, "minishell: cd: too many arguments\n");
	else if (ft_doublstrlen(command->cmd) == 2)
		ft_elseif(minishell, command, buff);
	else if (ft_doublstrlen(command->cmd) == 1)
		ft_elseif2(minishell, buff);
	return ;
}
