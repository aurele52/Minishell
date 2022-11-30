/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:34:11 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/30 10:52:15 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *minishell, t_command *command)
{
	char	*str;
	char	*buff;

	buff = ft_malloc(PATH_MAX, minishell->garbage);
	if (!buff)
		ft_exit(minishell, "malloc error\n");
	if (getcwd(buff, PATH_MAX))
	{
		write(command->ofdout, buff, ft_strlen(buff));
		write(command->ofdout, "\n", 1);
		return ;
	}
	else
	{
		str = ft_searchinenv(minishell, "PWD");
		if (str)
		{
			write(command->ofdout, str, ft_strlen(str));
			write(command->ofdout, "\n", 1);
		}
		return ;
	}
	minishell->laststatus = 0;
}
