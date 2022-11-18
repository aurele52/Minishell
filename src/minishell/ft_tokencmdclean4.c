/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmdclean4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:59:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/17 19:00:18 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expandsimplequote(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	str = token->str;
	str++;
	while (str[i])
		i++;
	str[i - 1] = 0;
	token->str = str;
}
