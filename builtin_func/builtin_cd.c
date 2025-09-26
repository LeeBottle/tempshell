/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:27 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:27 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path(char **argv)
{
	char	*path;

	if (argv[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_shell_sig = 1;
			return (NULL);
		}
	}
	else
		path = argv[1];
	return (path);
}

static void	chdir_path(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		g_shell_sig = 1;
	}
	else
		g_shell_sig = 0;
}

void	ft_cd(char **argv)
{
	int		i;
	char	*path;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_shell_sig = 1;
		return ;
	}
	path = get_path(argv);
	if (path == NULL)
		return ;
	chdir_path(path);
}
