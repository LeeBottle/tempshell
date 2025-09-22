#include "../minishell.h"

static void	sort_envp(char **envp_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strcmp(envp_copy[j], envp_copy[j + 1]) > 0)
			{
				temp = envp_copy[j];
				envp_copy[j] = envp_copy[j + 1];
				envp_copy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_list_stdout(char **envp_copy, int count)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		equal_sign = ft_strchr(envp_copy[i], '=');
		if (equal_sign)
		{
			write(1, envp_copy[i], equal_sign - envp_copy[i]);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equal_sign + 1, 1);
			ft_putstr_fd("\"", 1);
		}
		else
			ft_putstr_fd(envp_copy[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	export_list(t_shell *sh)
{
	char	**envp_copy;
	int		i;
	int		count;

	count = 0;
	while (sh->envp[count])
		count++;
	envp_copy = malloc(sizeof(char *) * (count + 1));
	if (!envp_copy)
		return ;
	i = 0;
	while (i < count)
	{
		envp_copy[i] = sh->envp[i];
		i++;
	}
	envp_copy[i] = NULL;
	sort_envp(envp_copy, count);
	print_list_stdout(envp_copy, count);
	free(envp_copy);
	sh->last_status = 0;
}
