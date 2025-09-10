#include "../minishell.h"

void	ft_pwd()
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("minishell: pwd");
		shell_sig = 1;
		return ;
	}
	ft_putstr_fd(temp, 1);
	ft_putstr_fd("--\n", 1);
	free(temp);
	shell_sig = 0;
}
