#include "../minishell.h"

int	execute(t_shell *sh, t_cmd *cmds)
{
	pid_t	last_pid;
	int		prev_pipe;

	if (cmds == NULL)
		return (0);
	if (cmds->argv && cmds->argv[0] && ft_strncmp(cmds->argv[0], "exit", 5) == 0 &&\
		cmds->next == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		if (cmds->argv[1] && cmds->argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell_sig = 1;
			return (0);
		}
		if (cmds->argv[1])
			shell_sig = ft_atoi(cmds->argv[1]);
		return (1);
	}
	if (cmds->next == NULL && is_builtin(cmds))
	{
		is_direct(sh, cmds);
		return (0);
	}
	prev_pipe = -1;
	last_pid = -1;
	process_cmd(sh, cmds, &prev_pipe, &last_pid);
	if (prev_pipe != -1)
		close(prev_pipe);
	wait_processes(sh, last_pid);
	return (0);
}
