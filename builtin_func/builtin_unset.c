#include "../minishell.h"

static void	add_new_env(char **env, char *result)
{
	free_envp(env);
	env = ft_split(result, '\n');
}

static int	key_init(char *env_var, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(env_var, key, key_len) == 0 && \
		(env_var[key_len] == '=' || env_var[key_len] == '\0'))
		return (1);
	return (0);
}

static void	del_env(char **env, char *key)
{
	char	*temp;
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (env[i])
	{
		if (!key_init(env[i], key))
		{
			if (result[0] != '\0')
			{
				temp = ft_strjoin(result, "\n");
				free(result);
				result = temp;
			}
			temp = ft_strjoin(result, env[i]);
			free(result);
			result = temp;
		}
		i++;
	}
	add_new_env(env, result);
	free(result);
}

void	ft_unset(char **env, char **argv)
{
	int	i;

	i = 1;
	if (argv[i] == NULL)
		return ;
	while (argv[i])
	{
		del_env(env, argv[i]);
		i++;
	}
	shell_sig = 0;
}
