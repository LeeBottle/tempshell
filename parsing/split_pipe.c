#include "../minishell.h"

void split_pipe(const char **line, t_token **head, t_token **tail)
{
    t_token *node;

	node = (t_token *)malloc(sizeof(t_token));
    if (!node)
        return;
    node->val   = ft_strdup("|");
    node->type  = TOK_PIPE;
    node->quote = Q_NONE;
    node->next  = NULL;
    if (!(*head))
        *head = node;
    else
        (*tail)->next = node;
    *tail = node;
    (*line)++;
}
