/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejo <sejo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:58:13 by sejo              #+#    #+#             */
/*   Updated: 2025/09/02 16:00:08 by sejo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

t_cmd	*start_new_cmd(t_cmd **head, t_cmd **tail)
{
	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	
	if (!*head)
		*head = cmd;
	else
		(*tail)->next = cmd;
	*tail = cmd;
	return (cmd);	
}

void	print_cmds(t_cmd *head)
{
	int i;
	t_cmd *cur;
	t_list *h;

	cur = head;
	while (cur)
	{
		printf("==== NEW CMD ====\n");

		// argv 출력
		if (cur->argv)
		{
			i = 0;
			while (cur->argv[i])
			{
				printf("argv[%d] = %s\n", i, cur->argv[i]);
				i++;
			}
		}
		else
			printf("argv = (null)\n");

		// infile/outfile/append 출력
		printf("infile  = %s\n", cur->infile ? cur->infile : "(null)");
		printf("outfile = %s\n", cur->outfile ? cur->outfile : "(null)");
		printf("append  = %s\n", cur->append ? cur->append : "(null)");

		// heredoc 출력
		if (cur->heredoc)
		{
			printf("heredoc = ");
			h = cur->heredoc;
			while (h)
			{
				printf("%s", (char *)h->content);
				if (h->next)
					printf(" | "); // 여러 줄이면 구분
				h = h->next;
			}
			printf("\n");
		}
		else
			printf("heredoc = (null)\n");

		cur = cur->next;
	}
}