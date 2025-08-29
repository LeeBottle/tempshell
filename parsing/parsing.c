#include "../minishell.h"

static void temp (t_token *input)
{
	for (t_token *p = input; p; p = p->next) {
        const char *tn =
            p->type==TOK_PIPE   ? "PIPE"   :
            p->type==TOK_STDIN  ? "<"      :
            p->type==TOK_STDOUT ? ">"      :
            p->type==TOK_HEREDOC? "<<"     :
            p->type==TOK_APPEND ? ">>"     : "WORD";
        if (p->type == TOK_WORD && p->val)
            printf("[%-4s]%s\n", tn, p->val);
        else
            printf("[%-4s]\n", tn);
    }
}

void	parsing(t_shell *sh, char *input)
{
	t_token *t;
	
	t = split_value(sh, input);
	if (pipe_end(sh, &t))
        return;
	if (validate_syntax(sh, t))
	{
        free_tokens(t);
        return;
    }
	temp (t);
	execute(sh, t);
    free_tokens(t);
}

//<<추가