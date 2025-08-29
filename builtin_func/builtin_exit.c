#include "../minishell.h"

void	ft_exit(t_shell *sh)
{
	ft_putstr_fd("exit\n", 1);
	exit(sh->last_status);
}