/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:22:54 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/29 17:22:56 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_updatepwd(t_minishell *minishell, char *buff)
{
	if (ft_envvarexist(minishell->actenv, "PWD"))
		ft_lstdelone(ft_envvarexist(minishell->actenv, "PWD"), 0);
	ft_addvarenv(minishell, "PWD", buff);
}
