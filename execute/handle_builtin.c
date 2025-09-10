#include "../minishell.h"

int func_builtin(char **env, t_cmd *cmd)
{
	char *command;

	command = cmd->argv[0];
	if (ft_strncmp(command, "echo", 5) == 0)
		ft_echo(cmd->argv);
	else if (ft_strncmp(command, "cd", 3) == 0)
		ft_cd(cmd->argv);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(command, "export", 7) == 0)
		ft_export(env, cmd->argv);
	else if (ft_strncmp(command, "unset", 6) == 0)
		ft_unset(env, cmd->argv);
	else if (ft_strncmp(command, "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(command, "exit", 5) == 0)
		ft_exit();
	else
		return (0);
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	char	*command;

	if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL)
		return (0);
	command = cmd->argv[0];
	if (ft_strncmp(command, "echo", 5) == 0 ||
		ft_strncmp(command, "cd", 3) == 0 ||
		ft_strncmp(command, "pwd", 4) == 0 ||
		ft_strncmp(command, "export", 7) == 0 ||
		ft_strncmp(command, "unset", 6) == 0 ||
		ft_strncmp(command, "env", 4) == 0 ||
		ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}
