#include "../minishell.h"

static t_quote quote_type(char c)
{
    if (c == '\'')
        return Q_SINGLE;
    else if (c == '\"')
        return Q_DOUBLE;
    return Q_NONE;
}

static char *extract_quoted_segment(const char **line, char quote)
{
    const char *start;
    size_t len;
    char *seg;
	int i;

    (*line)++;
    start = *line;
    while (**line && **line != quote)
        (*line)++;
    if (**line != quote)
        return NULL;
    len = (size_t)(*line - start);
    seg = (char *)malloc(len + 1);
    if (!seg)
        return NULL;
	i = 0;
	while (i < len)
	{
        seg[i] = start[i];
		i++;
	}
    seg[len] = '\0';
    (*line)++;
    return seg;
}

static char *quote_char(const char **line, t_quote *qsummary)
{
    char quote;
    char *seg;
    t_quote qtype;

    quote = **line;
    qtype = quote_type(quote);
    if (qtype == Q_NONE)
        return NULL;
    seg = extract_quoted_segment(line, quote);
    if (!seg)
        return NULL;
    if (*qsummary == Q_NONE)
        *qsummary = qtype;
    else if (*qsummary != qtype)
        *qsummary = Q_NONE;
    return seg;
}

int quoted_segment(const char **line, char **acc, t_quote *qsummary)
{
    char *seg;
    char *tmp;

	seg = quote_char(line, qsummary);
    if (!seg)
        return 0;
    tmp = ft_strjoin(*acc, seg);
    free(*acc);
    free(seg);
    if (!tmp)
        return 0;
    *acc = tmp;
    return 1;
}

