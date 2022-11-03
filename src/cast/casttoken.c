/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casttoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:44:06 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/02 12:44:43 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_type(t_list *list)
{
	t_token	*token;

	token = (t_token *)list->content;
	return (token->type);
}

char	*ft_str(t_list *list)
{
	t_token	*token;

	token = (t_token *)list->content;
	return (token->str);
}
