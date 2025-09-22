#include "../minishell.h"

int handle_redirections(t_cmd *cmd)
{
	int fd;

	if (cmd->in_type == 0)
	{
		if (cmd->infile)
		{
			fd = open(cmd->infile, O_RDONLY);
			if (fd < 0)
			{
				perror(cmd->infile);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else if(cmd->in_type == 1)
	{
		if (cmd->heredoc_fd)
		{
			dup2(cmd->heredoc_fd, STDIN_FILENO);
			close(cmd->heredoc_fd);
		}
	}
	if (cmd->out_type == 0)
	{
		if (cmd->outfile)
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(cmd->outfile);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	if (cmd->out_type == 1)
	{
		if (cmd->append)
		{
			fd = open(cmd->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(cmd->append);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	return (0);
}

void	is_direct(t_shell *sh, t_cmd *cmds)
{
	int stdin_backup;
	int stdout_backup;

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
	return;
}
