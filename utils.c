/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:25:54 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:25:55 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	free_tokens(t_token *t)
{
	t_token	*n;

	while (t)
	{
		n = t->next;
		free(t->val);
		free(t);
		t = n;
	}
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
