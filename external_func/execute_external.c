#include "../minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	execute_external(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	int		is_path_search;

	is_path_search = 0;
	if (ft_strchr(cmd->argv[0], '/'))
		path = cmd->argv[0];
	else
	{
		path = get_cmd_path(cmd->argv[0], sh->envp);
		is_path_search = 1;
	}
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, sh->envp);
	perror(cmd->argv[0]);
	if (is_path_search)
		free(path);
	exit(126);
}
