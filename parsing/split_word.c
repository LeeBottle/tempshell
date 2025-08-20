#include "../minishell.h"

static int etc_char(const char **line, char **acc)
{
    size_t	acc_len;
    char	*tmp;

    acc_len = ft_strlen(*acc);
    tmp = malloc((acc_len + 2) * sizeof(char));
    if (!tmp)
    {
        free(*acc);
        shell_sig = 1;
        return 0;
    }
    ft_memcpy(tmp, *acc, acc_len);
    tmp[acc_len] = **line;
    tmp[acc_len + 1] = '\0';
    free(*acc);
    *acc = tmp;
    (*line)++;
    return 1;
}

static void process_character(const char **line, char **acc, t_quote *qsummary)
{
    if (is_quote(**line))
    {
        if (!quoted_segment(line, acc, qsummary))
        {
            shell_sig = 1;
            free(*acc);
            *acc = NULL;
            return;
        }
    }
    else
    {
        if (!etc_char(line, acc))
        {
            free(*acc);
            *acc = NULL;
            return;
        }
    }
}

static void word_node(t_token **head, t_token **tail, char *acc, t_quote qsummary)
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
    node->quote = qsummary;
    node->next = NULL;
    if (!*head)
        *head = node;
    else
        (*tail)->next = node;
    *tail = node;
}

void split_word(const char **line, t_token **head, t_token **tail)
{
    char *acc;
    t_quote qsummary;

    acc = ft_strdup("");
    qsummary = Q_NONE;
    if (!acc)
    {
        shell_sig = 1;
        return;
    }
    while (**line && !is_space(**line) && !is_meta(**line))
    {
        process_character(line, &acc, &qsummary);
        if (!acc)
            return;
    }
    if (acc && acc[0] != '\0')
        word_node(head, tail, acc, qsummary);
    else
        free(acc);
}
