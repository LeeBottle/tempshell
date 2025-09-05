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
		if (ft_strncmp(sh->envp[i], key, key_len) == 0 && sh->envp[i][key_len] == '=')
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
		return;
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

void	ft_export(t_shell *sh, char **argv)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	if (argv[1] == NULL)
	{
		export_list(sh);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j]  == '=')
				break;
			j++;
		}
		if (i == 0 || !ft_isalpha(argv[i][0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			sh->last_status = 1;
		}
		else
		{
			key = ft_substr(argv[i], 0, j);
			value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j - 1);
			if (!update_existing_env(sh, key, value))
				add_new_env(sh, key, value);
			free(key);
			free(value);
			sh->last_status = 0;
		}
		i++;
	}
}
