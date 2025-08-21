#include "../minishell.h"

static void word_node(t_token **head, t_token **tail, char *acc)
{
	t_token *node;

	node = (t_token *)malloc(sizeof(t_token));
    if (!node)
    {
        free(acc);
        shell_sig = 1;
        return;
    }
    node->val = acc;
    node->type = TOK_WORD;
    node->next = NULL;
    if (!*head)
        *head = node;
    else
        (*tail)->next = node;
    *tail = node;
}

void split_word(t_shell *sh, char **line, t_token **head, t_token **tail)
{
    char *acc;

    acc = ft_strdup("");
    if (!acc)
    {
        shell_sig = 1;
        return;
    }
    while (**line && !is_space(**line) && !is_meta(**line))
    {
        process_character(sh, line, &acc);
        if (!acc)
            return;
    }
    if (acc)
    {
        if (acc[0] != '\0')
            word_node(head, tail, acc);
        else
            free(acc);
    }
}
