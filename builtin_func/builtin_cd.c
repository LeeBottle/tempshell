#include "../minishell.h"

void	ft_cd(t_shell *sh, t_token *input)
{
	char	*path;

	input = input->next;
	if (input == NULL || input->type != TOK_WORD)
		path = getenv("HOME");
	else
		path = input->val;
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("No such file or directory\n", 2);
        sh->last_status = 1;
	}
	else
		sh->last_status = 0;
}
