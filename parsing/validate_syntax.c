#include "../minishell.h"

static int  is_redir(t_toktype ty)
{
    return (ty == TOK_STDIN || ty == TOK_STDOUT
         || ty == TOK_APPEND || ty == TOK_HEREDOC);
}

static const char *tok_lexeme(t_token *t)
{
    if (!t)
		return "\\n";
    if (t->type == TOK_STDIN)
		return "<";
    if (t->type == TOK_STDOUT)
		return ">";
    if (t->type == TOK_APPEND)
		return ">>";
    if (t->type == TOK_HEREDOC)
		return "<<";
	if (t->val != NULL)
		return t->val;
	else
		return "";
}

static int  syntax_error(t_shell *sh, t_token *t)
{
    write(2, "zsh: parse error near `", 23);
    write(2, tok_lexeme(t), ft_strlen(tok_lexeme(t)));
    write(2, "'\n", 2);
    sh->last_status = 258;
    return 1;
}

int validate_syntax(t_shell *sh, t_token *t)
{
    t_token *cur;

	cur = t;
    if (!cur)
		return 0;
    while (cur)
	{
        if (cur->type == TOK_PIPE)
		{
            if (!cur->next || cur->next->type == TOK_PIPE)
                return syntax_error(sh, cur->next);
        }
		else if (is_redir(cur->type))
		{
            if (!cur->next || cur->next->type != TOK_WORD)
                return syntax_error(sh, cur->next);
        }
        cur = cur->next;
    }
    return 0;
}
