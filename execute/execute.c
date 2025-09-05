#include "../minishell.h"

static int handle_redirections(t_cmd *cmd)
{
	int fd;

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
/*	if (cmd->heredoc)
	{
	}*/
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
	return (0);
}

static int func_builtin(t_shell *sh, t_cmd *cmd)
{
	char *command;

	command = cmd->argv[0];
	if (ft_strncmp(command, "echo", 5) == 0)
		ft_echo(sh, cmd->argv);
	else if (ft_strncmp(command, "cd", 3) == 0)
		ft_cd(sh, cmd->argv);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		ft_pwd(sh);
	else if (ft_strncmp(command, "export", 7) == 0)
		ft_export(sh, cmd->argv);
	else if (ft_strncmp(command, "unset", 6) == 0)
		ft_unset(sh, cmd->argv);
	else if (ft_strncmp(command, "env", 4) == 0)
		ft_env(sh);
	else if (ft_strncmp(command, "exit", 5) == 0)
		ft_exit(sh);
	else
		return (0);
	return (1);
}

void    execute(t_shell *sh, t_cmd *cmd)
{
	int stdin_backup;
	int stdout_backup;

	if (cmd == NULL || cmd->argv[0] == NULL)
		return;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (handle_redirections(cmd) != 0)
		sh->last_status = 1;
	else
	{
		if (!func_builtin(sh, cmd))
			execute_external(sh, cmd); 
	}
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
