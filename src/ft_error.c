#include "minishell.h"

void	ft_error(t_minishell *minishell, char *str)
{
	if (minishell->garbagecmd != NULL)
		ft_posclear(minishell->garbagecmd, 0);
	if (minishell->tokenlist != NULL)
		ft_posclear(minishell->tokenlist, 0);
	if (str)
		write(2, str, ft_strlen(str));
}