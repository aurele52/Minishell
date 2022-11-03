#include "minishell.h"

void	ft_unset(t_minishell *minishell, t_command *command)
{
	t_list	*envlist;

	envlist = ft_envlist(minishell, command->cmd[1]);
	if (envlist != 0)
		ft_lstdelone(envlist, 0);
	minishell->laststatus = 0;
}