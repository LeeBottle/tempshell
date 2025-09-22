#include "../minishell.h"

/*static void temp (t_token *input)
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
}*/

void	parsing(t_shell *sh, char *input)
{
	t_token *t;
    t_cmd	*cmds;
	
	t = split_value(sh, input);
    if (validate_syntax(sh, t)) //파이프 뒤에 파이프가 올시 에러처리를 위한 조치
    {
        free_tokens(t);
        return;
    }
	if (pipe_end(sh, &t))
        return;
	cmds = token_to_cmd(t); // 토큰 -> t_cmd 변환 + heredoc readline
	execute(sh, cmds);
    free_tokens(t);
}

//<<추가