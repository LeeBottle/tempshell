/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejo <sejo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:48:45 by sejo              #+#    #+#             */
/*   Updated: 2025/09/03 17:43:36 by sejo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	append_argv(t_cmd *cmd, char *val)
{
	int	i;
	char	**new_argv;

	i =0;
	if(!cmd || !val)
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

/*void handle_heredoc(t_cmd *cmd, char *limiter)
{
	char *line;
	t_list	*node;
	t_list	*last;

	if (!cmd || !limiter)
		return ;
	last = cmd->heredoc;
	while (last && last->content)
		last = last->next;
	while ((line = readline("> ")) && strcmp(line, limiter))
	{
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			break;
		}
		if (!cmd->heredoc)
			cmd->heredoc = node;
		else
			last->next = node;
		last = node;
	}
	free(line);
}*/

static void heredoc_child(t_cmd *cmd, char *limiter)
{
    char *line;
    t_list *node;
    t_list *last = NULL;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);

    while (1)
    {
        line = readline("> ");
        if (!line) // Ctrl+D
        {
            printf("minishell: warning: here-document delimited by end-of-file (wanted `%s`)\n", limiter);
            exit(0);
        }
        if (ft_strncmp(line, limiter, 0) == 0)
        {
            free(line);
            exit(0);
        }
        node = ft_lstnew(line);
        if (!node) { free(line); exit(1); }
        if (!cmd->heredoc)
            cmd->heredoc = node;
        else
            last->next = node;
        last = node;
    }
}

void handle_heredoc(t_cmd *cmd, char *limiter)
{
    pid_t pid;
    int status;

    if (!cmd || !limiter)
        return;
    pid = fork();
    if (pid < 0)
        return; // fork 실패
    if (pid == 0)
        heredoc_child(cmd, limiter); // 자식에서 heredoc 수행
    waitpid(pid, &status, 0);
	waitpid(pid, &status, 0);
	if (status == 130)
	{
	    cmd->heredoc = NULL;
	    shell_sig = 1;
	}
}

static void	handle_redir(t_cmd *cmd, t_token *tok)
{
	if (tok->type == TOK_STDIN && tok->next)
		cmd->infile = ft_strdup(tok->next->val);
	if (tok->type == TOK_STDOUT && tok->next)
		cmd->outfile = ft_strdup(tok->next->val);
	if (tok->type == TOK_APPEND && tok->next)
		cmd->append = ft_strdup(tok->next->val);
}

static void	pros_token(t_cmd **cmd, t_cmd **head, t_cmd **tail, t_token **cur)
{
	if (!*cmd)
		*cmd = start_new_cmd(head, tail);
	if ((*cur)->type == TOK_WORD)
		append_argv(*cmd, (*cur)->val); // argv 배열에 새로운 단어 val 추가
	else if ((*cur)->type == TOK_HEREDOC && (*cur)->next)
	{
		handle_heredoc(*cmd, (*cur)->next->val);
		*cur = (*cur)->next;
	}
	else if ((*cur)->type == TOK_STDIN || (*cur)->type == TOK_STDOUT ||
		 (*cur)->type == TOK_APPEND)
		handle_redir(*cmd, *cur);
	else if ((*cur)->type == TOK_PIPE)
		*cmd = NULL;
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
		pros_token(&cmd, &head, &tail, &cur);
		cur = cur->next;
	}
	print_cmds(head);
	return (head);
}
