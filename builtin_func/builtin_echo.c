#include "../minishell.h"

static int	opt(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-' || argv[1] == '\0')
		return (0);
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (argv[i] && ft_strncmp(argv[i], "-", 1) == 0 && opt(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (newline == 1)
		ft_putstr_fd("\n", 1);
	shell_sig = 0;
}
