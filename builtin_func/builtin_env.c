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

void	ft_env(t_shell *sh, char **argv)
{
	int	i;
	int	j;

	j = 0;
	while (argv[j])
		j++;
	if (j > 1)
	{
		ft_putstr_fd("env: ‘", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("’: No such file or directory\n", 1);
		shell_sig = 127;
		return ;
	}
	i = 0;
	while (sh->envp[i])
	{
		ft_putendl_fd(sh->envp[i], 1);
		i++;
	}
}
