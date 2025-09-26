/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:57 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:58 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	if (cmd->in_type == 0)
	{
		if (infile_fd(cmd->infile))
			return (1);
	}
	else if (cmd->in_type == 1)
	{
		if (heredoc_fd(cmd->heredoc_fd))
			return (1);
	}
	if (cmd->out_type == 0)
	{
		if (outfile_fd(cmd->outfile))
			return (1);
	}
	else if (cmd->out_type == 1)
	{
		if (append_fd(cmd->append))
			return (1);
	}
	return (0);
}

void	is_direct(t_shell *sh, t_cmd *cmds)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (handle_redirections(cmds) != 0)
		g_shell_sig = 1;
	else
		func_builtin(sh, cmds);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return ;
}

static int	output_check(t_cmd *current)
{
	int	fd;

	if (current->outfile)
	{
		fd = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(current->outfile);
			return (1);
		}
		close(fd);
	}
	return (0);
}

static int	append_check(t_cmd *current)
{
	int	fd;

	if (current->append)
	{
		fd = open(current->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(current->append);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	outfile_checker(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->out_type == 0)
		{
			if (output_check(current))
				return (1);
		}
		else if (current->out_type == 1)
		{
			if (append_check(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
