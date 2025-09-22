#include "../minishell.h"

static void	execute_command(t_shell *sh, t_cmd *cmd)
{
	if (handle_redirections(cmd) != 0)
		exit(1);
	if (cmd->argv[0] == NULL)
		exit(0);
	if (func_builtin(sh, cmd))
		exit(sh->last_status);
	else
		execute_external(sh, cmd);
}

void	execute(t_shell *sh, t_cmd *cmds)
{
	int		pipe_fd[2];
	int		prev_pipe_read_end = -1;
	pid_t	pid;
	pid_t	last_pid = -1;
	t_cmd	*current_cmd = cmds;

	if (cmds == NULL)
		return;
	if (cmds->next == NULL  && is_builtin(cmds))
	{
		is_direct(sh, cmds);
		return;
	}
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL && pipe(pipe_fd) == -1)
			return ((void)perror("minishell: pipe"));
		pid = fork();
		if (pid == -1)
			return ((void)perror("minishell: fork"));
		else if (pid == 0)
		{
			if (prev_pipe_read_end != -1)
			{
				dup2(prev_pipe_read_end, STDIN_FILENO);
				close(prev_pipe_read_end);
			}
			if (current_cmd->next != NULL)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			execute_command(sh, current_cmd);
		}
		if (prev_pipe_read_end != -1)
			close(prev_pipe_read_end);
		if (current_cmd->next != NULL)
		{
			close(pipe_fd[1]);
			prev_pipe_read_end = pipe_fd[0];
		}
		last_pid = pid;
		current_cmd = current_cmd->next;
	}
	if (prev_pipe_read_end != -1)
		close(prev_pipe_read_end);
	int status;
	pid_t waited_pid;
	while ((waited_pid = wait(&status)) > 0)
	{
		if (waited_pid == last_pid && WIFEXITED(status))
			sh->last_status = WEXITSTATUS(status);
	}
}
