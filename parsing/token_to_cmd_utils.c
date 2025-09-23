/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:58:13 by sejo              #+#    #+#             */
/*   Updated: 2025/09/22 13:29:17 by byeolee          ###   ########.fr       */
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
	cmd->heredoc_fd = -1;
	cmd->in_type = -1;
	cmd->out_type = -1;
	cmd->heredoc_interrupted = 0;
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
		printf("in_type  = %d\n", cur->in_type);
		printf("out_type  = %d\n", cur->out_type);
		if (cur->in_type == 1 && cur->heredoc_fd >= 0)
		{
		    printf("heredoc_fd = %d\n", cur->heredoc_fd);
		
		    // 디버깅용: heredoc 내용 확인
		    char buf[1024];
		    int n;
		
		    lseek(cur->heredoc_fd, 0, SEEK_SET); // fd 처음으로
		    n = read(cur->heredoc_fd, buf, sizeof(buf) - 1);
		    if (n > 0)
		    {
		        buf[n] = '\0';
		        printf("heredoc content = %s\n", buf);
		    }
		}
		else
		{
		    printf("heredoc = (null)\n");
		}
		cur = cur->next;
	}
}