/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:47 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:48 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			(sh->envp[i][key_len] == '=' || sh->envp[i][key_len] == '\0'))
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
	g_shell_sig = 0;
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
	g_shell_sig = 0;
}

void	export_key_only(t_shell *sh, char **argv, int i)
{
	char	*key;
	int		k;
	int		key_len;

	key = argv[i];
	if (!key_chekcer(key))
	{
		export_error(key);
		return ;
	}
	k = 0;
	key_len = ft_strlen(key);
	while (sh->envp[k])
	{
		if (ft_strncmp(sh->envp[k], key, key_len) == 0 && \
			(sh->envp[k][key_len] == '\0' || sh->envp[k][key_len] == '='))
		{
			g_shell_sig = 0;
			return ;
		}
		k++;
	}
	add_key_only(sh, key);
	g_shell_sig = 0;
}
