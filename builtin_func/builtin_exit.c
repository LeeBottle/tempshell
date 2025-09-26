#include "../minishell.h"

int	ft_exit(t_cmd *cmds)
{
	ft_putstr_fd("exit\n", 1);
	if (cmds->argv[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell_sig = 1;
		return (0);
	}
	if (cmds->argv[1])
		shell_sig = ft_atoi(cmds->argv[1]);
	return (1);
}
