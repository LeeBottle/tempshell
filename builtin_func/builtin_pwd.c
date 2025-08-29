#include "../minishell.h"

void	ft_pwd(t_shell *sh, t_token *input)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("minishell: pwd");
		sh->last_status = 1;
		return ;
	}
	ft_putstr_fd(temp, 1);
	ft_putstr_fd("\n", 1);
	free(temp);
	sh->last_status = 0;
}