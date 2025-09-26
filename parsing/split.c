/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:59:49 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 16:54:38 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*split_value(t_shell *sh, char *line)
{
	t_token_list	t_list;

	t_list.head = NULL;
	t_list.tail = NULL;
	while (*line)
	{
		while (*line && is_space(*line))
			line++;
		if (!*line)
			break ;
		if (*line == '|')
		{
			split_pipe(&line, &t_list);
			continue ;
		}
		if (*line == '<' || *line == '>')
		{
			split_redir(&line, &t_list);
			continue ;
		}
		split_word(sh, &line, &t_list);
	}
	return (t_list.head);
}
