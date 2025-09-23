#include "../minishell.h"

void	ft_exit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	ft_putstr_fd("exit\n", 1);
	if (i > 1)
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
	exit(shell_sig);
}
