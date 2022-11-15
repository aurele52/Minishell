/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:48:41 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/02 13:12:08 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_lasti(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	i--;
// 	if (str[i] == '+')
// 		str[i] = 0;
// 	return (str);
// }

// t_env	*ft_envtoken(t_minishell *minishell, char *str)
// {
// 	int		lol;
// 	t_list	*line;

// 	lol = 0;
// 	str = ft_lasti(str);
// 	line = minishell->actenv->start;
// 	while (line != minishell->actenv->start || lol++ == 0)
// 	{
// 		if (ft_strcmp(ft_name(line->content), str) == 0)
// 			return ((t_env *)line->content);
// 		line = line->next;
// 	}
// 	return (0);
// }

// int	ft_egalplus(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			return (0);
// 		if (str[i] == '+')
// 		{
// 			if (i == 0 && str[i + 1] != '=')
// 				return (1);
// 			else if (str[i - 1] != '=' && str[i + 1] != '=')
// 				return (1);
// 			else
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_searchname(t_minishell *minishell, char *str)
// {
// 	int		i;
// 	char	*ret;

// 	i = 0;
// 	while (str[i] && str[i] != '=' && str[i] != '+')
// 		i++;
// 	ret = ft_substr(str, 0, i, minishell->garbage);
// 	if (!ret)
// 		ft_exit(minishell, "malloc error\n");
// 	return (ret);
// }

// char	*ft_searchvalue(t_minishell *minishell, char *str)
// {
// 	int		i;
// 	char	*ret;

// 	i = 0;
// 	while (str[i] && str[i] != '=' && str[i] != '+')
// 		i++;
// 	if (str[i] == '+' || str[i] == '=')
// 		i++;
// 	if (str[i] == '+' || str[i] == '=')
// 		i++;
// 	str = str + i;
// 	i = 0;
// 	while (str[i])
// 		i++;
// 	ret = ft_substr(str, 0, i, minishell->garbage);
// 	if (!ret)
// 		ft_exit(minishell, "malloc error\n");
// 	return (ret);
// }

// void	ft_haveinenv(t_minishell *minishell, t_env *line, char *cmd, char *env)
// {
// 	char	*temp;
// 	int		ti;
// 	if (cmd[line->lname] == '+' || cmd[line->lname + 1] == '+')
// 	{
// 		temp = ft_searchvalue(minishell, cmd);
// 		line->value = ft_strjoin(line->value, temp, minishell->garbage);
// 		if (!line->value)
// 			ft_exit(minishell, "malloc error\n");
// 	}
// 	else
// 	{
// 		ti = ft_strlen(env);
// 		line->value = ft_substr(cmd, line->lname + 1, ti, minishell->garbage);
// 	}
// 	if (!line->value)
// 		ft_exit(minishell, "malloc error\n");
// 	line->lvalue = ft_strlen(line->value);
// }

// void	ft_doesnthaveinenv(t_minishell *minishell, char *command)
// {
// 	t_env	*line;

// 	line = ft_malloc(sizeof(*line), minishell->garbage);
// 	if (!line)
// 		ft_exit(minishell, "malloc error\n");
// 	ft_lstnew(line, minishell->actenv, minishell->garbage);
// 	if (!minishell->actenv->start->back)
// 		ft_exit(minishell, "malloc error\n");
// 	line->name = ft_searchname(minishell, command);
// 	if (!line->name)
// 		ft_exit(minishell, "malloc error\n");
// 	line->lname = ft_strlen(line->name);
// 	line->value = ft_searchvalue(minishell, command);
// 	if (!line->value)
// 		ft_exit(minishell, "malloc error\n");
// 	line->lvalue = ft_strlen(line->value);
// }

// int	ft_checkcmd1(t_minishell *minishell, char *cmd1)
// {
// 	if (cmd1 == 0)
// 	{
// 		ft_error(minishell, "nop\n");
// 		return (1);
// 	}
// 	if (cmd1[0] == 0 || cmd1[0] == '=' || (cmd1[0] <= '9' && cmd1[0] >= '0')) 
// 	/*
// 		ici cmd[0] doit forcement etre alpha si autre alors on rentre dans condition
// 	*/
// 	{
// 		ft_error(minishell, "minishell: export: `': not a valid identifier\n");
// 		return (1);
// 	}
// 	/*
// 		le nom d'une variable peut contenir alphanum et '_' 
// 	*/
// 	return (0);
// }

// void	ft_export(t_minishell *minishel, t_command *command)
// {
// 	int		i;
// 	t_env	*line;
// 	char	*cmd1;

// 	cmd1 = command->cmd[1];
// 	i = 1;
// 	if (ft_checkcmd1(minishel, cmd1) == 1)
// 		return ;
// 	while (command->cmd[i])
// 	{
// 		if (ft_egalplus(command->cmd[i]))
// 		{
// 			ft_error(minishel, "minishell: export: not a valid identifier\n");
// 			return ;
// 		}
// 		line = ft_envtoken(minishel, ft_searchname(minishel, command->cmd[i]));
// 		if (line)
// 			ft_haveinenv(minishel, line, command->cmd[i], minishel->env[i]);
// 		else
// 			ft_doesnthaveinenv(minishel, command->cmd[i]);
// 		i++;
// 	}
// }






void	ft_soloexport(t_command *command)
{
	write(command->ofdout, "You choose to use", ft_strlen("You choose to use"));
	write(command->ofdout, " export on its", ft_strlen(" export on its"));
	write(command->ofdout, " own, and as an", ft_strlen(" own, and as an"));
	write(command->ofdout, " undefine behavior", ft_strlen(" undefine behavior"));
	write(command->ofdout, ", it will not do", ft_strlen(", it will not do"));
	write(command->ofdout, " anything but this", ft_strlen(" anything but this"));
	write(command->ofdout, ".\n", ft_strlen(".\n"));
}

int	ft_cmdexportvalid(char *cmd)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (cmd[++i])
		if (!ft_isalpha((int)cmd[i]) || cmd[i] != '_')
		{
			check++;
			break ;
		}
	if (cmd[i] != '=')
		check++;
	if (check != 0)
		return (1);
	else
		return (0);
}

char	**ft_cmdexport(t_minishell *minishell, char *cmd)
{
	char	**var;
	int		lname;
	int		lvalue;

	var = ft_malloc(sizeof(*var) * 3, minishell->garbage);
	if (!var)
		ft_exit(minishell, "malloc error\n");
	lname = ft_strlenchar(cmd, '=');
	lvalue = ft_strlen(cmd) - ft_strlenchar(cmd, '=') - 1;
	var[0] = ft_substr(cmd, 0, lname, minishell->garbage);
	var[1] = ft_substr(cmd, lname + 1, lvalue, minishell->garbage);
	return (var);
}

void	ft_export(t_minishell *minishell, t_command *command)
{
	int		i;
	char	**cmdexport;

	if (ft_doublstrlen(command->cmd) == 1)
	{
		ft_soloexport(command);
		return ;
	}
	i = 0;
	while (command->cmd[++i])
	{
		if (ft_cmdexportvalid(command->cmd[i]))
		{
			cmdexport = ft_cmdexport(minishell, command->cmd[i]);
			if (ft_envvarexist(minishell->actenv, cmdexport[0]))
				ft_lstdelone(ft_envvarexist(minishell->actenv, cmdexport[0]), 0);
			ft_addvarenv(minishell, cmdexport[0], cmdexport[1]);
		}
		else
		{
			ft_error(minishell, /* recup message d'erreur sur bash */"error in export");
			return ;
		}
	}
	minishell->laststatus = 0;
	return ;
}