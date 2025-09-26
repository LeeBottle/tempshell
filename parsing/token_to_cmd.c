/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:48:45 by sejo              #+#    #+#             */
/*   Updated: 2025/09/23 17:25:06 by byeolee          ###   ########.fr       */
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
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(val);
	if (!new_argv[i])
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
			free(cmd->argv[i++]);
		free(new_argv);
		return ;
	}
	new_argv[i + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}

void heredoc_child(char *limiter, int write_fd)
{
    char *line;

    rl_catch_signals = 0;
    signal(SIGINT, heredoc_sigint); // Ctrl+C 처리
    signal(SIGQUIT, SIG_IGN);

    while (1)
    {
        line = readline("> ");
        if (!line) // Ctrl+D
        {
            printf("minishell: warning: here-document delimited by end-of-file (wanted `%s`)\n", limiter);
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
    close(write_fd);
    exit(0);
}

void handle_heredoc(t_cmd *cmd, char *limiter)
{
    int             pipefd[2];
    pid_t           pid;
    int             status;
    struct termios  term_backup; // 터미널 설정을 저장할 '사진기' 변수

    /*
     * [사진 찍기📸]
     * 학생 조수(자식 프로세스)를 부르기 전에, 현재 깨끗한 교실 상태(터미널 설정)를
     * term_backup 이라는 변수에 저장(사진 찍기)합니다.
     * tcgetattr 함수가 바로 이 역할을 해요.
     */
    tcgetattr(STDIN_FILENO, &term_backup);

    // 우리가 Ctrl+C를 눌렀을 때 메인 셸(선생님)이 영향받지 않도록 잠시 신호를 무시해요.
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (pipe(pipefd) == -1)
        return;

    pid = fork(); // 학생 조수(자식 프로세스)를 만듭니다.
    if (pid < 0)
        return;

    if (pid == 0) // 여기는 학생 조수가 일하는 공간이에요.
    {
        close(pipefd[0]);
        // 학생 조수는 Ctrl+C 비상벨이 울리면 heredoc_sigint 함수를 실행하도록 규칙을 정해요.
        signal(SIGINT, heredoc_sigint);
        heredoc_child(limiter, pipefd[1]);
    }
    else // 여기는 선생님이 학생 조수를 기다리는 공간이에요.
    {
        close(pipefd[1]);
        waitpid(pid, &status, 0); // 학생 조수의 일이 끝날 때까지 기다립니다.

        /*
         * [사진 보고 정리하기✨]
         * 학생 조수의 일이 어떻게 끝났든(잘 끝났든, 도망쳤든) 상관없이,
         * 아까 찍어뒀던 사진(term_backup)을 보고 교실(터미널)을
         * 원래의 깨끗한 상태로 되돌립니다.
         * tcsetattr 함수가 이 역할을 담당해요.
         */
        tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);

        // 이제 선생님은 다시 Ctrl+C 신호를 받도록 원래대로 돌려놓습니다.
        signal(SIGINT, sigint_handler);

        // 만약 학생 조수가 Ctrl+C(종료 코드 130) 때문에 나갔다면,
        if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
        {
            // heredoc 작업이 중단되었다고 표시합니다.
            shell_sig = 1;
            cmd->heredoc_fd = -1;
            cmd->heredoc_interrupted = 1;
			return ;
        }
        else // 정상적으로 끝났다면,
        {
            cmd->heredoc_fd = pipefd[0];
            cmd->heredoc_interrupted = 0;
        }

        if (cmd->infile)
        {
            free(cmd->infile);
            cmd->infile = NULL;
        }
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
		append_argv(*cmd, (*cur)->val); // argv 배열에 새로운 단어 val 추가
	else if ((*cur)->type == TOK_HEREDOC && (*cur)->next)
	{
		handle_heredoc(*cmd, (*cur)->next->val);
		if ((*cmd)->heredoc_interrupted)
		{
			//*cur = (*cur)->next;
			return (1);
		}
		(*cmd)->in_type = 1;
		*cur = (*cur)->next;
	}
	else if ((*cur)->type == TOK_STDIN || (*cur)->type == TOK_STDOUT ||
		 (*cur)->type == TOK_APPEND)
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
		if(pros_token(&cmd, &head, &tail, &cur))
		{
			free_cmds(head);
			return (0);
		}
		cur = cur->next;
	}
	//print_cmds(head);
	return (head);
}
//추가