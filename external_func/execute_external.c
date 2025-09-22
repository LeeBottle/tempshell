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

	path = get_cmd_path(cmd->argv[0], sh->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, sh->envp);
	perror(cmd->argv[0]);
	free(path);
	exit(126);
}
