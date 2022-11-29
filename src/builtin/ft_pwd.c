/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:34:11 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/16 15:26:31 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *minishell, t_command *command)
{
	char	*str;

	str = ft_searchinenv(minishell, "PWD");
	if (access(str, F_OK))
	{
		str = ft_strdup("pwd: error retrieving curren", minishell->garbagecmd);
		str = ft_strjoin(str, "t directory: getcwd: ca", minishell->garbagecmd);
		str = ft_strjoin(str, "nnot access parent dire", minishell->garbagecmd);
		str = ft_strjoin(str, "ctories: No such file o", minishell->garbagecmd);
		str = ft_strjoin(str, "r directory\n", minishell->garbagecmd);
		if (!str)
			ft_exit(minishell, "malloc error\n");
		ft_error(minishell, str);
		return ;
	}
/* 	if (!str)
	{

	} */
	write(command->ofdout, str, ft_strlen(str));
	write(command->ofdout, "\n", 1);
	minishell->laststatus = 0;
}
