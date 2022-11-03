
#include "minishell.h"

void	ft_preexit(t_minishell *minishell, t_command *command)
{
	ft_exit(minishell, command->cmd[1]);
}