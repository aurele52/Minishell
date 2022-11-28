/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellinit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:10:23 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/28 18:10:25 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_minishell2(t_minishell *minishell)
{
	char	*str;

	str = 0;
	str = ft_readline("Minishell> ", minishell->garbagecmd);
	if (!str && g_heredoc == 42)
	{
		ft_exit(minishell, "exit\n");
		return (NULL);
	}
	else if ((!str && g_heredoc == 130) || str[0] == '\0')
		return (NULL);
	else
		return (str);
}
