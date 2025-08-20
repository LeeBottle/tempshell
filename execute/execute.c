#include "../minishell.h"

void execute(t_shell *sh, t_token *input)
{
	for (t_token *p = input; p; p = p->next) {
        const char *tn =
            p->type==TOK_PIPE   ? "PIPE"   :
            p->type==TOK_STDIN  ? "<"      :
            p->type==TOK_STDOUT ? ">"      :
            p->type==TOK_HEREDOC? "<<"     :
            p->type==TOK_APPEND ? ">>"     : "WORD";
        const char *qn =
            p->quote==Q_SINGLE  ? "single" :
            p->quote==Q_DOUBLE  ? "double" : "none";
        if (p->type == TOK_WORD && p->val)
            printf("[%-4s/%6s] %s\n", tn, qn, p->val);
        else
            printf("[%-4s/%6s]\n", tn, qn);
    }
	sh->last_status = 127;
}