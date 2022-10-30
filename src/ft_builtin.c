/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:25:54 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/28 14:18:58 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell, t_command *command)
{
	ft_posprint(minishell, minishell->actenv, &ft_printenv, command->ofdout);	
	minishell->laststatus = 0;
}

void	ft_pwd(t_minishell *minishell, t_command *command)
{
	char	*str;

	str = ft_searchinenv(minishell, "PWD");
	if (access(str, F_OK))
	{
		ft_error(minishell, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return ;
	}
	write(command->ofdout, str, ft_strlen(str));
	write(command->ofdout, "\n", 1);
	minishell->laststatus = 0;
}

void	ft_preexit(t_minishell *minishell, t_command *command)
{
	ft_exit(minishell, command->cmd[1]);
}

int	ft_strhaveegal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_envlist(t_minishell *minishell, char *str)
{
	int		lol;
	t_list	*line;

	lol = 0;
	line = minishell->actenv->start;
	while (line != minishell->actenv->start || lol++ == 0)
	{
		if (ft_strcmp(ft_name(line->content), str) == 0)
			return (line);
		line = line->next;
	}
	return (0);
}

char	*ft_lasti(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '+')
		str[i] = 0;
	return (str);
}

t_env	*ft_envtoken(t_minishell *minishell, char *str)
{
	int		lol;
	t_list	*line;

	lol = 0;
	str = ft_lasti(str);
	line = minishell->actenv->start;
	while (line != minishell->actenv->start || lol++ == 0)
	{
		if (ft_strcmp(ft_name(line->content), str) == 0)
			return ((t_env *)line->content);
		line = line->next;
	}
	return (0);
}

void	ft_printexport(t_command *command, t_env *env)
{
	write(command->ofdout, "export ", 7);
	write(command->ofdout, env->name, env->lname);
	if (env->lvalue != 0)
	{
		write(command->ofdout, "=", 1);
		write(command->ofdout, "\"", 1);
		write(command->ofdout, env->value, env->lvalue);
		write(command->ofdout, "\"", 1);
	}
	write(command->ofdout, "\n", 1);
}

int	ft_strcmp2(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (str1 == 0 || str2 == 0)
		return (-1);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

t_pos	*ft_posdup(t_pos *pos, t_pos *garbage)
{
	t_pos	*new;
	t_list	*temp;

	new = ft_setpos(garbage);
	if (!new)
		return (0);
	temp = pos->start;
	while (temp != pos->start->back)
	{
		ft_lstnew(temp->content, new, garbage);
		if (!new->start->back)
			return (0);
		temp = temp->next;
	}
	ft_lstnew(temp->content, new, garbage);
	if (!new->start->back)
		return (0);
	return (new);
}

void	ft_envexport(t_minishell *minishell, t_command *command)
{
	t_list	*env;
	t_env	*envtoken;
	t_env	*memtoken;
	t_list	*mem;
	t_pos	*dup;

	dup = ft_posdup(minishell->actenv, minishell->garbagecmd);
	if (!dup)
		ft_exit(minishell, "malloc error\n");
	while (*dup->size != 0)
	{
		env = dup->start;
		mem = env;
		env = env->next;
		while (env != env->pos->start)
		{
			envtoken = (t_env *)env->content;
			memtoken = (t_env *)mem->content;
			if (ft_strcmp2(envtoken->name, memtoken->name) <= 0)
				mem = env;
			env = env->next;
		}
		envtoken = (t_env *)env->content;
		memtoken = (t_env *)mem->content;
		if (ft_strcmp2(envtoken->name, memtoken->name) <= 0)
			mem = env;
		ft_printexport(command, memtoken);
		ft_lstdelone(mem, 0);
	}
}

int	ft_egalplus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == '+')
		{
			if (i == 0 && str[i + 1] != '=')
				return (1);
			else if (str[i - 1] != '=' && str[i + 1] != '=')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	*ft_searchname(t_minishell *minishell, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	ret = ft_substr(str, 0, i, minishell->garbage);
	if (!ret)
		ft_exit(minishell, "malloc error\n");
	return (ret);
}

char	*ft_searchvalue(t_minishell *minishell, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+' || str[i] == '=')
		i++;
	if (str[i] == '+' || str[i] == '=')
		i++;
	str = str + i;
	i = 0;
	while (str[i])
		i++;
	ret = ft_substr(str, 0, i, minishell->garbage);
	if (!ret)
		ft_exit(minishell, "malloc error\n");
	return (ret);
}

char	*ft_lastcmd(t_minishell *minishell, t_command *command)
{
	int		i;
	char	*str;

	i = 0;
	while (command->cmd[i])
		i++;
	str = ft_strjoin("_=", command->cmd[i - 1], minishell->garbagecmd);
	return (str);
}

void	ft_underscore(t_minishell *minishell, t_command *base)
{
	t_command	*command;

	command = ft_malloc(sizeof(t_command), minishell->garbagecmd);
	command->cmd = ft_malloc(sizeof(char *) * 3, minishell->garbagecmd);
	command->cmd[0] = ft_strdup("export", minishell->garbagecmd);
	command->cmd[1] = ft_lastcmd(minishell, base);
	command->cmd[2] = 0;
	ft_export(minishell, command);
}

void	ft_export(t_minishell *minishell, t_command *command)
{
	int		i;
	t_env	*line;

	i = 1;
	if (command->cmd[1] == 0)
	{
		ft_error(minishell, "nop\n");
		return ;
	}
	if (command->cmd[1][0] == 0 || command->cmd[1][0] == '=' || (command->cmd[1][0] <= '9' && command->cmd[1][0] >= '0'))
	{
		ft_error(minishell, "minishell: export: `': not a valid identifier\n");
		return ;
	}
	while (command->cmd[i])
	{
		if (ft_egalplus(command->cmd[i]))
		{
			ft_error(minishell, "minishell: export: `': not a valid identifier\n");
			return ;
		}
		line = ft_envtoken(minishell, ft_searchname(minishell, command->cmd[i]));
		if (line)
		{
			if (command->cmd[i][line->lname] == '+' || command->cmd[i][line->lname + 1] == '+')
				line->value = ft_strjoin(line->value, ft_searchvalue(minishell, command->cmd[i]), minishell->garbage);
			else
				line->value = ft_substr(command->cmd[i], line->lname + 1, ft_strlen(minishell->env[i]), minishell->garbage);
			if (!line->value)
				ft_exit(minishell, "malloc error\n");
			line->lvalue = ft_strlen(line->value);
		}
		else
		{
			line = ft_malloc(sizeof(*line), minishell->garbage);
			if (!line)
				ft_exit(minishell, "malloc error\n");
			ft_lstnew(line, minishell->actenv, minishell->garbage);
			if (!minishell->actenv->start->back)
				ft_exit(minishell, "malloc error\n");
			line->name = ft_searchname(minishell, command->cmd[i]);
			if (!line->name)
				ft_exit(minishell, "malloc error\n");
			line->lname = ft_strlen(line->name);
			line->value = ft_searchvalue(minishell, command->cmd[i]);
			if (!line->value)
				ft_exit(minishell, "malloc error\n");
			line->lvalue = ft_strlen(line->value);
		}
		i++;
	}
	minishell->laststatus = 0;
}

void	ft_unset(t_minishell *minishell, t_command *command)
{
	t_list	*envlist;

	envlist = ft_envlist(minishell, command->cmd[1]);
	if (envlist != 0)
		ft_lstdelone(envlist, 0);
	minishell->laststatus = 0;
}

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
//	printf("HOME = %s\n", varenv->value);//
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
	if (!ft_envvarexist(minishell->actenv, "PWD"))
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
	/*
		peut etre definir PATH_MAX dans le *.h
		*/
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (ft_doublstrlen(command->cmd) > 2)
		ft_error(minishell, "minishell: cd: too many arguments\n");
	else if (ft_doublstrlen(command->cmd) == 2)
	{
		if (ft_PWDcheck(minishell))
			return ;
		if (chdir(command->cmd[1]) == 0)
		{
			if (getcwd(buff, PATH_MAX))
				ft_updateenv(minishell, buff);
			minishell->laststatus = 0;
		}
		else
		{
			str = ft_strdup("minishell: cd: ", minishell->garbagecmd);
			str = ft_strjoin(str, command->cmd[1], minishell->garbagecmd);
			str = ft_strjoin(str, ft_strdup(": No such file or directory\n", minishell->garbagecmd), minishell->garbagecmd);
			if (!str)
				ft_exit(minishell, "malloc error\n");
			ft_error(minishell, str);
		}
	}
	else if (ft_doublstrlen(command->cmd) == 1)
	{
		if (ft_PWDcheck(minishell))
			return ;
		list = ft_envvarexist(minishell->actenv, "HOME");
		if (ft_homechdir(list->content) == 0)
		{
			if (getcwd(buff, PATH_MAX))
				ft_updateenv(minishell, buff);
			minishell->laststatus = 0;
		}
		else
			ft_error(minishell, "minishell: cd: no home defined\n");
	}
}

void	ft_builtin(t_minishell *minishell, t_command *command)
{
//	ft_underscore(minishell, command);
	if (!ft_strcmp(command->cmd[0], "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command->cmd[0], "cd"))
		ft_cd(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		ft_pwd(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		ft_preexit(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "export"))
		ft_export(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "unset"))
		ft_unset(minishell, command);
}

int	ft_isbuiltin(t_command *command)
{
	if (!ft_strcmp(command->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		return (1);
	return (0);
}
