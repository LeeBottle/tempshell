#include "../minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	if (cmd->in_type == 0)
	{
		if (infile_fd(cmd->infile))
			return (1);
	}
	else if (cmd->in_type == 1)
	{
		if (heredoc_fd(cmd->heredoc_fd))
			return (1);
	}
	if (cmd->out_type == 0)
	{
		if (outfile_fd(cmd->outfile))
			return (1);
	}
	else if (cmd->out_type == 1)
	{
		if (append_fd(cmd->append))
			return (1);
	}
	return (0);
}

void	is_direct(t_shell *sh, t_cmd *cmds)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (handle_redirections(cmds) != 0)
		shell_sig = 1;
	else
		func_builtin(sh, cmds);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return ;
}
