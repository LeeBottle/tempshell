/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:26:23 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 19:34:21 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_cmd_node(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->append);
	if (cmd->heredoc_fd >= 0)
		close(cmd->heredoc_fd);
	free(cmd);
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free_cmd_node(current);
		current = next;
	}
}

int	parsing(t_shell *sh, char *input)
{
	t_token	*t;
	t_cmd	*cmds;
	int		should_exit;

	t = split_value(sh, input);
	if (validate_syntax(t))
	{
		free_tokens(t);
		return (0);
	}
	if (pipe_end(sh, &t))
	{
		free_tokens(t);
		return (0);
	}
	cmds = token_to_cmd(t);
	if (cmds)
		should_exit = execute(sh, cmds);
	else
		should_exit = 0;
	free_tokens(t);
	free_cmds(cmds);
	return (should_exit);
}
