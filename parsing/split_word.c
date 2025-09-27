/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:58:43 by sejo              #+#    #+#             */
/*   Updated: 2025/09/27 14:24:32 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	word_node(t_token_list *list, char *acc)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
	{
		free(acc);
		g_shell_sig = 1;
		return ;
	}
	node->val = acc;
	node->type = TOK_WORD;
	node->next = NULL;
	if (!list->head)
		list->head = node;
	else
		(list->tail)->next = node;
	list->tail = node;
}

void	split_word(t_shell *sh, char **line, t_token_list *list)
{
	char	*acc;

	acc = ft_strdup("");
	if (!acc)
	{
		free(acc);
		g_shell_sig = 1;
		return ;
	}
	while (**line && !is_space(**line) && !is_meta(**line))
	{
		process_character(sh, line, &acc, list);
		if (!acc)
			return ;
	}
	if (acc && acc[0] != '\0')
	{
		word_node(list, acc);
	}
	else
		free(acc);
}
