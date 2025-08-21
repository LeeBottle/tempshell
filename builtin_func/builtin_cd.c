#include "../minishell.h"

void	ft_cd(t_shell *sh, t_token *input)
{
	char	*path;

	if (input->next->val == NULL)
		path = getenv("HOME");
	else
		path = input->next->val;
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		sh->last_status = 1;
	}
	else
		sh->last_status = 0;
}
