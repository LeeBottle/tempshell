/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejo <sejo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:59:33 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 15:40:00 by sejo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_toktype	get_redir_type_1(char **line)
{
	t_toktype	rtype;

	if ((*line)[1] == '<')
	{
		rtype = TOK_HEREDOC;
		*line += 2;
	}
	else
	{
		rtype = TOK_STDIN;
		*line += 1;
	}
	return (rtype);
}

static t_toktype	get_redir_type_2(char **line)
{
	t_toktype	rtype;

	if ((*line)[1] == '>')
	{
		rtype = TOK_APPEND;
		*line += 2;
	}
	else
	{
		rtype = TOK_STDOUT;
		*line += 1;
	}
	return (rtype);
}

static t_toktype	get_redir_type(char **line)
{
	if (**line == '<')
	{
		return (get_redir_type_1(line));
	}
	else
	{
		return (get_redir_type_2(line));
	}
}

void	split_redir(char **line, t_token_list *list)
{
	t_toktype	rtype;
	t_token		*node;

	rtype = get_redir_type(line);
	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return ;
	node->val = ft_strdup("");
	node->type = rtype;
	node->next = NULL;
	if (!list->head)
		list->head = node;
	else
		(list->tail)->next = node;
	list->tail = node;
}
