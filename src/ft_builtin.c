/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:25:54 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/26 16:10:29 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell)
{
	ft_posprint(minishell, minishell->actenv, &ft_printenv);	
}

void	ft_pwd(t_minishell *minishell)
{
	char	*str;

	str = ft_searchinenv(minishell, "PWD");
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
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

t_env	*ft_envtoken(t_minishell *minishell, char *str)
{
	int		lol;
	t_list	*line;

	lol = 0;
	line = minishell->actenv->start;
	while (line != minishell->actenv->start || lol++ == 0)
	{
		if (ft_strcmp(ft_name(line->content), str) == 0)
			return ((t_env *)line->content);
		line = line->next;
	}
	return (0);
}

void	ft_export(t_minishell *minishell, t_command *command)
{
	int		i;
	t_env	*line;

	i = 1;
	while (command->cmd[i])
	{
		if (ft_strhaveegal(command->cmd[i]) == 1)
		{
			line = ft_envtoken(minishell, ft_strdup((ft_split(command->cmd[i], '=', minishell->garbage)[0]), minishell->garbage));
			if (line)
			{
				line->value = ft_substr(command->cmd[i], line->lname + 1, ft_strlen(minishell->env[i]), minishell->garbage);
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
				line->name = ft_strdup(ft_split(command->cmd[i], '=', minishell->garbage)[0], minishell->garbage);
				line->lname = ft_strlen(line->name);
				line->value = ft_substr(command->cmd[i], line->lname + 1, ft_strlen(command->cmd[i]) - 1 - line->lname, minishell->garbage);
				line->lvalue = ft_strlen(line->value);
			}
		}
		i++;
	}
}

void	ft_unset(t_minishell *minishell, t_command *command)
{
	t_list	*envlist;

	envlist = ft_envlist(minishell, command->cmd[1]);
	if (envlist != 0)
		ft_lstdelone(envlist, 0);
}

// void	ft_export(t_minishell *minishell, t_command *command)
// {
// 	/*	only accept alphanum and underscore to define env variables name
// 		if no '=' in cmd[1 et +] do nothing
// 		if '=' and nothing behind put value at '\0'
// 		for each arg make the check and conversion*/
// 	/*	prend un env au debut de l'exec, fait ses operations a partir de cet env
// 		qu'ils sauvegarde dans le nouveau qui sera renvoyer a la fin*/
// 	/*	may need to remake the parsing for export*/
// 	if (ft_envvarexist(minishell, "str"))
// 	{
// 		/* replace envact value by new one */
// 	}
// 	else
// 	{
// 		/* lstnew with command */
// 	}
// }

void	ft_builtin(t_minishell *minishell, t_command *command)
{
	if (!ft_strcmp(command->cmd[0], "echo"))
	{
		printf("ECHO_MAISON\n"); //
		ft_echo(command);
	}
	else if (!ft_strcmp(command->cmd[0], "cd"))
	{
		// ft_cd(minishell, command);
		printf("CD_MAISON\n"); //
		printf("ft_cd = %i\n", ft_cd(minishell, command));//
		char buff[PATH_MAX];//
		if (getcwd(buff, PATH_MAX))//
			printf("curent directory = %s\n", buff);//
	}
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		ft_pwd(minishell);
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(minishell);
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
