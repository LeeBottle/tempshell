/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:48:45 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 19:17:23 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_argv(t_cmd *cmd, char *val)
{
	int		i;
	char	**new_argv;

	i = 0;
	if (!cmd || !val)
		return ;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	new_argv[i] = ft_strdup(val);
	new_argv[i + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}

void	handle_heredoc(t_cmd *cmd, char *limiter)
{
	int				pipefd[2];
	pid_t			pid;
	int				status;
	struct termios	term_backup;

	status = 0;
	tcgetattr(STDIN_FILENO, &term_backup);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipefd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(limiter, pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		cmd->heredoc_fd = pipefd[0];
		heredoc_parent_close(pid, status, term_backup, cmd);
	}
	return ;
}

static void	handle_redir(t_cmd *cmd, t_token *tok)
{
	if (tok->type == TOK_STDIN && tok->next)
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(tok->next->val);
		cmd->in_type = 0;
		if (cmd->heredoc_fd >= 0)
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
	}
	if (tok->type == TOK_STDOUT && tok->next)
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(tok->next->val);
		cmd->append = NULL;
		cmd->out_type = 0;
	}
	if (tok->type == TOK_APPEND && tok->next)
	{
		free(cmd->append);
		cmd->append = ft_strdup(tok->next->val);
		cmd->outfile = NULL;
		cmd->out_type = 1;
	}
}

static int	pros_token(t_cmd **cmd, t_cmd **head, t_cmd **tail, t_token **cur)
{
	if (!*cmd)
		*cmd = start_new_cmd(head, tail);
	if ((*cur)->type == TOK_WORD)
		append_argv(*cmd, (*cur)->val);
	else if ((*cur)->type == TOK_HEREDOC && (*cur)->next)
	{
		handle_heredoc(*cmd, (*cur)->next->val);
		if ((*cmd)->heredoc_interrupted)
		{
			*cur = (*cur)->next;
			return (1);
		}
		(*cmd)->in_type = 1;
		*cur = (*cur)->next;
	}
	else if ((*cur)->type == TOK_STDIN || (*cur)->type == \
		TOK_STDOUT || (*cur)->type == TOK_APPEND)
	{
		handle_redir(*cmd, *cur);
		if ((*cur)->next)
			*cur = (*cur)->next;
	}
	else if ((*cur)->type == TOK_PIPE)
		*cmd = NULL;
	return (0);
}

t_cmd	*token_to_cmd(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*cmd;
	t_token	*cur;

	head = NULL;
	tail = NULL;
	cmd = NULL;
	cur = tokens;
	while (cur)
	{
		if (pros_token(&cmd, &head, &tail, &cur))
			return (0);
		cur = cur->next;
	}
	return (head);
}
