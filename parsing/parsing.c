#include "../minishell.h"

void	parsing(t_shell *sh, char *input)
{
	t_token *t;
	
	t = split_value(input);
	if (validate_syntax(sh, t))
	{
        free_tokens(t);
        return;
    }
	execute(sh, t);
    free_tokens(t);
}
