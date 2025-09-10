#include "../minishell.h"

void	ft_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(shell_sig);
}
