/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:37 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:38 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	without_equal(t_shell *sh, char **argv, int i)
{
	if (!key_chekcer(argv[i]))
		export_error(argv[i]);
	else
		export_key_only(sh, argv, i);
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
			without_equal(sh, argv, i);
		else if (j > 0 && argv[i][j - 1] == '+')
			append_val(sh, argv, i, j);
		else if (j > 0)
			export_val(sh, argv, i, j);
		else
			export_error(argv[i]);
		i++;
	}
}
