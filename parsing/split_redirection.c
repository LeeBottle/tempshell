#include "../minishell.h"

static t_toktype get_redir_type_1(const char **line)
{
    t_toktype rtype;

    if ((*line)[1] == '<')
    {
        rtype = TOK_HEREDOC;
        *line += 2;
    }
    else
    {
        rtype = TOK_STDIN;
        *line += 1;
    }
    return rtype;
}

static t_toktype get_redir_type_2(const char **line)
{
    t_toktype rtype;

    if ((*line)[1] == '>')
    {
        rtype = TOK_APPEND;
        *line += 2;
    }
    else
    {
        rtype = TOK_STDOUT;
        *line += 1;
    }
    return rtype;
}

static t_toktype get_redir_type(const char **line)
{
    if (**line == '<')
    {
        return get_redir_type_1(line);
    }
    else
    {
        return get_redir_type_2(line);
    }
}

void split_redir(const char **line, t_token **head, t_token **tail)
{
    t_toktype rtype;
	t_token *node;

	rtype = get_redir_type(line);
	node = (t_token *)malloc(sizeof(t_token));
    if (!node)
		return;
    node->val   = ft_strdup("");
    node->type  = rtype;
    node->quote = Q_NONE;
    node->next  = NULL;
    if (!*head)
		*head = node;
    else
		(*tail)->next = node;
    *tail = node;
}
