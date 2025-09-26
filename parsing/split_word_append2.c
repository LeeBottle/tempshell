/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_append2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:55:53 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 19:37:55 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_value(t_shell *sh, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], key, key_len) == 0 && \
			sh->envp[i][key_len] == '=')
			return (&sh->envp[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

static char	*extract_var_name(char *str, int *len)
{
	char	*start;
	char	*var_name;

	start = str;
	if (ft_isdigit(*str))
	{
		*len = 1;
		return (ft_strdup(""));
	}
	while (ft_isalnum(*str) || *str == '_')
		str++;
	*len = (int)(str - start);
	if (*len == 0)
		return (ft_strdup(""));
	var_name = malloc(*len + 1);
	if (!var_name)
		return (NULL);
	ft_memcpy(var_name, start, *len);
	var_name[*len] = '\0';
	return (var_name);
}

static char	*question(char **line)
{
	if (**line == '?')
	{
		(*line)++;
		return (ft_itoa(g_shell_sig));
	}
	else if (!ft_isalpha(**line) && **line != '_')
	{
		if (!**line || is_space(**line) || is_quote(**line) || is_meta(**line))
			return (ft_strdup("$"));
		else if (ft_isdigit(**line))
		{
			(*line)++;
			return (ft_strdup(""));
		}
	}
	return (NULL);
}

char	*get_expanded_value(t_shell *sh, char **line)
{
	char	*var_name;
	char	*env_val;
	int		var_len;
	char	*result;

	(*line)++;
	result = question(line);
	if (result != NULL)
		return (result);
	var_name = extract_var_name(*line, &var_len);
	if (!var_name)
		return (NULL);
	*line += var_len;
	env_val = get_env_value(sh, var_name);
	free(var_name);
	if (env_val)
		return (ft_strdup(env_val));
	return (ft_strdup(""));
}

void	append_expanded_val(char **acc, char *expanded_val)
{
	char	*tmp;

	if (!expanded_val)
	{
		free(*acc);
		*acc = NULL;
		return ;
	}
	tmp = ft_strjoin(*acc, expanded_val);
	free(*acc);
	*acc = tmp;
	if (!*acc)
		g_shell_sig = 1;
}
