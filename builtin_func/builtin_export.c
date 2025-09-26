#include "../minishell.h"

static int	find_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_export(t_shell *sh, char **argv)
{
	int	i;
	int	j;

	if (argv[1] == NULL)
	{
		export_list(sh);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		j = find_equal(argv[i]);
		if (j < 0)
		{
			if (!key_chekcer(argv[i]))
				export_error(argv[i]);
		}
		else if (j > 0 && argv[i][j - 1] == '+')
			append_val(sh, argv, i, j);
		else if (j > 0)
			export_val(sh, argv, i, j);
		else
			export_error(argv[i]);
		i++;
	}
}
