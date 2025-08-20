#include "../minishell.h"

t_token *split_value(const char *line)
{
    t_token       *head = NULL;
    t_token       *tail = NULL;

    while (*line)
    {
        while (*line && is_space(*line))
            line++;
        if (!*line)
            break;
        if (*line == '|')
        {
            split_pipe(&line, &head, &tail);
            continue;
        }
        if (*line == '<' || *line == '>')
        {
            split_redir(&line, &head, &tail);
            continue;
        }
        split_word(&line, &head, &tail);
    }
    return head;
}
