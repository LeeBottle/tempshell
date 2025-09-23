#include "../minishell.h"

void	execute(t_shell *sh, t_cmd *cmds)
{
	int		fd[2];
	int		prev_pipe;
	pid_t	last_pid;
	t_cmd	*current_cmd;

	if (cmds == NULL)
		return ;
	if (cmds->next == NULL && is_builtin(cmds))
		return (is_direct(sh, cmds));
	prev_pipe = -1;
	last_pid = -1;
	process_cmd(sh, cmds, &prev_pipe, &last_pid);
	if (prev_pipe != -1)
		close(prev_pipe);
	wait_processes(sh, last_pid);
}
