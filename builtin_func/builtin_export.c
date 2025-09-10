#include "../minishell.h"

static int	update_existing_env(t_shell *sh, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_var;
	char	*temp;

	i = 0;
	key_len = ft_strlen(key);
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, key_len) == 0 && \
			sh->envp[i][key_len] == '=')
		{
			free(sh->envp[i]);
			temp = ft_strjoin(key, "=");
			new_var = ft_strjoin(temp, value);
			free(temp);
			sh->envp[i] = new_var;
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
		new_envp[count] =env[count];
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
	value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j - 1);
	if (!update_existing_env(env, key, value))
		add_new_env(env, key, value);
	free(key);
	free(value);
	shell_sig = 0;
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
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '=')
				break ;
			j++;
		}
		if (i == 0 || !ft_isalpha(argv[i][0]))
			error_code(argv[i]);
		else
			export_val(env, argv, i, j);
		i++;
	}
}
