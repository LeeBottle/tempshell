/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:58:13 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 17:16:46 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	heredoc_parent_close(pid_t pid, int status, \
	struct termios term_backup, t_cmd *cmd)
{
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
	signal(SIGINT, sigint_handler);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_shell_sig = 1;
		cmd->heredoc_fd = -1;
		cmd->heredoc_interrupted = 1;
		return ;
	}
	else
		cmd->heredoc_interrupted = 0;
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
}

void	heredoc_child(char *limiter, int write_fd)
{
	char	*line;

	rl_catch_signals = 0;
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document \
delimited by end-of-file (wanted `%s`)\n", limiter);
			exit(0);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			exit(0);
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	exit(0);
}

t_cmd	*start_new_cmd(t_cmd **head, t_cmd **tail)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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
