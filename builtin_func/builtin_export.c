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

char	*ft_export(t_shell *sh, t_token *input)
{
	int		i;
	char	*temp;
	char	*key;
	char	*value;

	input = input->next;
	if (input == NULL || input->type != TOK_WORD)
		return(export_list(sh));
	while (input != NULL)
	{
		i = 0;
		while (input->val[i] != '\0')
		{
			if (input->val[i] == '=')
				break;
			i++;
		}
		if (i == 0)
		{
			ft_putstr_fd("minishell: export: `",2);
			ft_putstr_fd(input->val, 2);
			ft_putstr_fd("': not a valid identifier\n",2);
		}
		key = ft_substr(input->val, 0, i);
		value = ft_substr(input->val, i + 1, ft_strlen(input->val) - i - 1);
		if (!update_existing_env(sh, key, value))
			add_new_env(sh, key, value);
		free(key);
		free(value);
		input = input->next;
	}
	return (0);
}
