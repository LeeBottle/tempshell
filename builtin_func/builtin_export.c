#include "../minishell.h"

static int	key_chekcer(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	update_existing_env(char **env, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_var;
	char	*temp;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && \
			env[i][key_len] == '=')
		{
			free(env[i]);
			temp = ft_strjoin(key, "=");
			new_var = ft_strjoin(temp, value);
			free(temp);
			env[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_new_env(char **env, char *key, char *value)
{
	int		count;
	char	**new_envp;
	char	*new_var;
	char	*temp;

	count = 0;
	while (env[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return ;
	count = 0;
	while (env[count])
	{
		new_envp[count] = env[count];
		count++;
	}
	temp = ft_strjoin(key, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	new_envp[count] = new_var;
	new_envp[count + 1] = NULL;
	free(env);
	env = new_envp;
}

static void	error_code(char *argv)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell_sig = 1;
}

static void	export_val(char **env, char **argv, int i, int j)
{
	char	*key;
	char	*value;

	key = ft_substr(argv[i], 0, j);
	if (!key_chekcer(key))
	{
		error_code(argv[i]);
		free(key);
		return ;
	}
	value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j - 1);
	if (!update_existing_env(env, key, value))
		add_new_env(env, key, value);
	free(key);
	free(value);
	shell_sig = 0;
}

static int find_equal(char *argv)
{
	int i;

	while (argv)
	{
		if(argv[i] == '=')
			break;
		i++;
	}
	return (i);
}

void	ft_export(char **env, char **argv)
{
	int		i;
	int		j;

	if (argv[1] == NULL)
	{
		export_list(env);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		j = find_equal(argv[i]);
		if (argv[i][j] == '=')
			export_val(env, argv, i, j);
		else
		{
			if (!key_chekcer(argv[i]))
				error_code(argv[i]);
		}
		i++;
	}
}
