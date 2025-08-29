#include "../minishell.h"

static int end_is_pipe(t_token *t)
{
	if (!t)
        return (0);
	while (t->next)
        t = t->next;
	if (t->type == TOK_PIPE)
		return (1);
	return (0);
}

int pipe_end(t_shell *sh, t_token **t_head)
{
    char    *input;
    t_token *last;
    t_token *new_tokens;

    while (end_is_pipe(*t_head))
    {
		input = readline("> ");
		printf("%s / %d\n", input, shell_sig);
		if (shell_sig == 1)
            return (1);
        if (!input)
        {
            ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
            ft_putstr_fd("exit\n", 2);
			free_tokens(*t_head);
            *t_head = NULL;
            exit(258);
        }
        if (*input)
        {
            add_history(input);
            new_tokens = split_value(sh, input);
            if (new_tokens)
            {
                last = *t_head;
                while (last && last->next)
                    last = last->next;
                if (last)
                    last->next = new_tokens;
            }
        }
        free(input);
    }
	return (0);
}
// ctrl+C 입력시 현재 입력 종료 -> minishell 종료x
// history에 |이전 history 덧붙히기
