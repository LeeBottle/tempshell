#include "../minishell.h"

static int	pre_processing(t_shell *sh, t_cmd *cmds, int *is_pipeline)
{
	if (cmds == NULL)
		return (0);
	if (outfile_checker(cmds) != 0)
	{
		shell_sig = 1;
		return (0);
	}
	if (ft_strncmp(cmds->argv[0], "exit", 5) == 0)
		return (ft_exit(cmds));
	if (cmds->next == NULL && is_builtin(cmds))
	{
		is_direct(sh, cmds);
		return (0);
	}
	*is_pipeline = 0;
	if (cmds && cmds->next)
		*is_pipeline = 1;
	return (1);
}

static void	main_loop(t_shell *sh, t_cmd *cmds, int is_pipeline)
{
	pid_t	last_pid;
	int		prev_pipe;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	prev_pipe = -1;
	last_pid = -1;
	process_cmd(sh, cmds, &prev_pipe, &last_pid);
	if (prev_pipe != -1)
		close(prev_pipe);
	wait_processes(sh, last_pid, is_pipeline);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	execute(t_shell *sh, t_cmd *cmds)
{
	int	is_pipeline;

	if (!pre_processing(sh, cmds, &is_pipeline))
		return (0);
	main_loop(sh, cmds, is_pipeline);
	return (0);
}
