#include "../minishell.h"

static char	*get_cmd_fullpath(char **paths, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char *cmd, char **env)
{
	char	*path_env;
	char	*full_path;
	char	**paths;
	int		i;

	if (!env || cmd == NULL)
		return (NULL);
	path_env = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		path_env = "/usr/local/sbin:/usr/local/\
bin:/usr/sbin:/usr/bin:/sbin:/bin";
	paths = ft_split(path_env, ':');
	full_path = get_cmd_fullpath(paths, cmd);
	free_split(paths);
	return (full_path);
}

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

static char	*find_cmd_in_paths(char *cmd, char **envp)
{
	char	**paths;
	char	*path_part;
	char	*full_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths && paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

void execute_external(t_shell *sh, t_cmd *cmd)
{
    pid_t pid;
    char *path;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        sh->last_status = 1;
        return;
    }
    if (pid == 0)
    {
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
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            sh->last_status = WEXITSTATUS(status);
    }
}
