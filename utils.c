#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int is_meta(char c)
{
	return (c=='|'||c=='<'||c=='>');
}

void free_tokens(t_token *t)
{
    while (t)
	{
        t_token *n = t->next;
        free(t->val);
        free(t);
        t = n;
    }
}