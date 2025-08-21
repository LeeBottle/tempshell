#include "../minishell.h"

static void opt(t_token **input, int *newline)
{
	char *opt;

	opt = (*input)->val;
	opt++;
	while (*opt != '\0')
	{
		if (*opt != 'n')
			return ;
		opt++;
	}
	printf("----\n");
	*newline = 0;
	(*input) = (*input)->next;
}

char	*ft_echo(t_shell *sh, t_token *input)
{
	int		newline;
    char    *result;
    char    *temp;

	newline = 1;
    result = ft_strdup("");
	input = input->next;
	if (input && ft_strncmp(input->val, "-", 1) == 0)
		opt(&input, &newline);
	while (input && input->type == TOK_WORD)
	{
		temp = ft_strjoin(result, input->val);
		free(result);
        result = temp;
        input = input->next;
		if (input && input->type == TOK_WORD)
        {
            temp = ft_strjoin(result, " ");
            free(result);
            result = temp;
        }
	}
	{
        temp = ft_strjoin(result, "\n");
        free(result);
        result = temp;
    }
    sh->last_status = 0;
    return (result);
}


