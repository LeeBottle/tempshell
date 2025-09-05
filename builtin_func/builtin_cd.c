#include "../minishell.h"

void	ft_cd(t_shell *sh, char **argv)
{
	int		i;
	char	*path;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	if (argv[1] == NULL)
		path = getenv("HOME");
	else
		path = argv[1];
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
