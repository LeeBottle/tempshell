/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:43:45 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 17:16:46 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	etc_char(char **line, char **acc)
{
	size_t	acc_len;
	char	*tmp;

	acc_len = ft_strlen(*acc);
	tmp = malloc((acc_len + 2) * sizeof(char));
	if (!tmp)
	{
		free(*acc);
		g_shell_sig = 1;
		return (0);
	}
	ft_memcpy(tmp, *acc, acc_len);
	tmp[acc_len] = **line;
	tmp[acc_len + 1] = '\0';
	free(*acc);
	*acc = tmp;
	(*line)++;
	return (1);
}

static void	single_quote(char **line, char **acc)
{
	(*line)++;
	while (**line && **line != '\'')
	{
		if (!etc_char(line, acc))
			return ;
	}
	if (**line == '\'')
		(*line)++;
	else if (**line != '\'')
	{
		free(*acc);
		*acc = NULL;
		g_shell_sig = 1;
		ft_putendl_fd("quote error", 2);
		return ;
	}
}

static void	double_quote(t_shell *sh, char **line, char **acc)
{
	char	*expanded_val;

	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$' && (*line)[1] && !is_space((*line)[1]) && \
			(*line)[1] != '\"' && (*line)[1] != '\'')
		{
			expanded_val = get_expanded_value(sh, line);
			append_expanded_val(acc, expanded_val);
			free(expanded_val);
			if (!*acc)
				return ;
		}
		else
		{
			if (!etc_char(line, acc))
				return ;
		}
	}
	if (**line == '\"')
		(*line)++;
	else if (**line != '\"')
		handle_unclosed_quote(acc);
}

static void	env(char *expanded_val, char **acc, t_token_list *list)
{
	char	**parts;
	int		i;

	parts = ft_split(expanded_val, ' ');
	if (expanded_val[0] == ' ')
	{
		if (*acc)
		{
			word_node(list, *acc);
			*acc = NULL;
		}
		i = 0;
		while (parts[i])
		{
			if (*parts[i])
				word_node(list, ft_strdup(parts[i]));
			i++;
		}
	}
	else
	{
		env_append(acc, list, parts);
	}
	free_split(parts);
	free(expanded_val);
}

void	process_character(t_shell *sh, \
	char **line, char **acc, t_token_list *list)
{
	char	*expanded_val;

	if (**line == '\'')
		single_quote(line, acc);
	else if (**line == '\"')
		double_quote(sh, line, acc);
	else if (**line == '$' && (*line)[1] && !is_space((*line)[1]) \
			&& (*line)[1] != '\"' && (*line)[1] != '\'')
	{
		expanded_val = get_expanded_value(sh, line);
		if (!expanded_val)
			return ;
		env(expanded_val, acc, list);
	}
	else
	{
		if (!etc_char(line, acc))
			return ;
	}
}
