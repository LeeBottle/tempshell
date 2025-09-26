/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:35 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:35 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	numer_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_shell_sig = 2;
}

int	ft_exit(t_cmd *cmds)
{
	ft_putstr_fd("exit\n", 1);
	if (cmds->argv[1] == NULL)
		return (1);
	if (!is_numer(cmds->argv[1]))
	{
		numer_error(cmds->argv[1]);
		return (1);
	}
	if (cmds->argv[1] && cmds->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_shell_sig = 1;
		return (0);
	}
	g_shell_sig = ft_atoi(cmds->argv[1]);
	return (1);
}
