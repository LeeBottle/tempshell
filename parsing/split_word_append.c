#include "../minishell.h"

static int etc_char(char **line, char **acc)
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

static void single_quote(char **line, char **acc)
{
	(*line)++;
    while (**line && **line != '\'')
    {
        if (!etc_char(line, acc))
            return;
    }
    if (**line == '\'')
        (*line)++;
}

static void double_quote(t_shell *sh, char **line, char **acc)
{
	char *expanded_val;

    (*line)++;
    while (**line && **line != '\"')
    {
        if (**line == '$' && (*line)[1] && !is_space((*line)[1]) && \
			(*line)[1] != '\"' && (*line)[1] != '\'')
        {
            expanded_val = get_expanded_value(sh, line);
            append_expanded_val(acc, expanded_val);
            if (!*acc)
                return;
        }
        else
        {
            if (!etc_char(line, acc))
                return;
        }
    }
    if (**line == '\"')
        (*line)++;
}

static void env(t_shell *sh, char **line, char **acc)
{
    char *expanded_val;

    expanded_val = get_expanded_value(sh, line);
    append_expanded_val(acc, expanded_val);
    if (!*acc)
        return;
}

void process_character(t_shell *sh, char **line, char **acc)
{
    if (**line == '\'')
		single_quote(line, acc);
    else if (**line == '\"')
		double_quote(sh, line, acc);
    else if (**line == '$' && (*line)[1] && !is_space((*line)[1]) \
			&& (*line)[1] != '\"' && (*line)[1] != '\'')
		env(sh, line, acc);
    else
    {
        if (!etc_char(line, acc))
            return;
    }
}
