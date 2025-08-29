#include "../minishell.h"

static void	add_new_env(t_shell *sh, char *result)
{
	free_envp(sh->envp);
	sh->envp = ft_split(result, '\n');
}

static int key_init(char *env_var, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(env_var, key, key_len) == 0 && \
		(env_var[key_len] == '=' || env_var[key_len] == '\0'))
		return (1);
	return (0);
}

static void	del_env(t_shell *sh, char *key)
{
	char	*temp;
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (sh->envp[i])
	{
		if (!key_init(sh->envp[i], key))
		{
			if (result[0] != '\0')
			{
				temp = ft_strjoin(result, "\n");
				free(result);
				result = temp;
			}
			temp = ft_strjoin(result, sh->envp[i]);
			free(result);
			result = temp;
		}
		i++;
	}
	add_new_env(sh, result);
	free(result);
}

void	ft_unset(t_shell *sh, t_token *input)
{
	input = input->next;
	if (input == NULL || input->type != TOK_WORD)
		return ;
	while (input != NULL && input->type == TOK_WORD)
	{
		del_env(sh, input->val);
		input = input->next;
	}
	sh->last_status = 0;
}