#include "../minishell.h"

static char	**input_envp(int i, int count, char **envp)
{
	char	**new_envp;

	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		i;
	int		count;

	if (!envp)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	new_envp = input_envp(i, count, envp);
	return (new_envp);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}
