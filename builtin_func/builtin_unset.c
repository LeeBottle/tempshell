/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:43 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:43 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_env(t_shell *sh, char *result)
{
	free_envp(sh->envp);
	sh->envp = ft_split(result, '\n');
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
	new_env(sh, result);
	free(result);
}

void	ft_unset(t_shell *sh, char **argv)
{
	int	i;

	i = 1;
	if (argv[i] == NULL)
		return ;
	while (argv[i])
	{
		del_env(sh, argv[i]);
		i++;
	}
	g_shell_sig = 0;
}
