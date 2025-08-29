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
	*newline = 0;
	(*input) = (*input)->next;
}

void	ft_echo(t_shell *sh, t_token *input)
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
		ft_putstr_fd(input->val, 1);
        input = input->next;
		if (input && input->type == TOK_WORD)
			ft_putstr_fd(" ", 1);
	}
	if (newline == 1)
		ft_putstr_fd("\n", 1);
    sh->last_status = 0;
}


