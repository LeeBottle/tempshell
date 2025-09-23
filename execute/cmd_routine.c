#include "../minishell.h"

static void	execute_command(t_shell *sh, t_cmd *cmd)
{
	if (cmd->argv[0] == NULL)
		exit(0);
	if (func_builtin(sh, cmd))
		exit(shell_sig);
	else
		execute_external(sh, cmd);
}

static void	child_process(t_shell *sh, t_cmd *cmd, int fd[2], int pv_pipe)
{
	if (cmd->in_type != -1)
	{
		handle_redirections(cmd);
	}
	if (pv_pipe != -1)
	{
		dup2(pv_pipe, STDIN_FILENO);
		close(pv_pipe);
	}
	if (cmd->next != NULL)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->argv[0] == NULL)
		exit(0);
	if (func_builtin(sh, cmd))
		exit(shell_sig);
	else
		execute_external(sh, cmd);
}

static void	parent_process(int fd[2], int *pv_pipe, t_cmd *cmd)
{
	if (*pv_pipe != -1)
		close(*pv_pipe);
	if (cmd->next != NULL)
	{
		close(fd[1]);
		*pv_pipe = fd[0];
	}
	if (cmd->in_type == 1 && cmd->heredoc_fd >= 0)
	{
		close(cmd->heredoc_fd);
	}
}

void	process_cmd(t_shell *sh, t_cmd *cmds, int *pv_pipe, pid_t *last_pid)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*current_cmd;

	current_cmd = cmds;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL && pipe(fd) == -1)
		{
			perror("minishell: pipe");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			return ;
		}
		else if (pid == 0)
			child_process(sh, current_cmd, fd, *pv_pipe);
		parent_process(fd, pv_pipe, current_cmd);
		*last_pid = pid;
		current_cmd = current_cmd->next;
	}
}

void	wait_processes(t_shell *sh, pid_t last_pid)
{
	int		status;
	pid_t	waited_pid;

	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid > 0)
		{
			if (waited_pid == last_pid && WIFEXITED(status))
				shell_sig = WEXITSTATUS(status);
		}
		else
			break ;
	}
}
