#include "../minishell.h"

static int	n_flag(const char *s)
{
	int i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_shell *sh, char **input)
{
	int i;

	i = 1;
	if (input[1] && n_flag(input[1]))
	{
		while (input[i] && n_flag(input[i]))
			i++;
		while (input[i])
		{
			write(1, input[i], ft_strlen(input[i]));
			if (input[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	else
	{
		while (input[i])
		{
			write(1, input[i], ft_strlen(input[i]));
			if (input[i + 1])
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
	sh->last_status = 0;
}


