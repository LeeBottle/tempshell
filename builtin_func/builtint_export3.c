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

static int	update_append_env(t_shell *sh, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_var;
	char	*old_var;
	char	*temp;

	i = 0;
	key_len = ft_strlen(key);
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, key_len) == 0 && \
					sh->envp[i][key_len] == '=')
		{
			temp = ft_strjoin(key, "=");
			old_var = ft_strjoin(temp, sh->envp[i] + key_len + 1);
			new_var = ft_strjoin(old_var, value);
			free(temp);
			free(old_var);
			free(sh->envp[i]);
			sh->envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_new_env(t_shell *sh, char *key, char *value)
{
	int		count;
	char	**new_envp;
	char	*new_var;
	char	*temp;

	count = 0;
	while (sh->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return ;
	count = 0;
	while (sh->envp[count])
	{
		new_envp[count] = sh->envp[count];
		count++;
	}
	temp = ft_strjoin(key, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	new_envp[count] = new_var;
	new_envp[count + 1] = NULL;
	free(sh->envp);
	sh->envp = new_envp;
}

void	export_val(t_shell *sh, char **argv, int i, int j)
{
	char	*key;
	char	*value;

	key = ft_substr(argv[i], 0, j);
	if (!key_chekcer(key))
	{
		export_error(argv[i]);
		free(key);
		return ;
	}
	value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j - 1);
	if (!update_existing_env(sh, key, value))
		add_new_env(sh, key, value);
	free(key);
	free(value);
	shell_sig = 0;
}

void	append_val(t_shell *sh, char **argv, int i, int j)
{
	char	*key;
	char	*value;

	key = ft_substr(argv[i], 0, j - 1);
	if (!key_chekcer(key))
	{
		export_error(argv[i]);
		free(key);
		return ;
	}
	value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j - 1);
	if (!update_append_env(sh, key, value))
		add_new_env(sh, key, value);
	free(key);
	free(value);
	shell_sig = 0;
}
