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

char	*get_cmd_path(char *cmd, char **env)
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
