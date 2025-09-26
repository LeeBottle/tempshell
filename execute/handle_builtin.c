/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:28:00 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:28:00 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	func_builtin(t_shell *sh, t_cmd *cmd)
{
	char	*command;

	command = cmd->argv[0];
	if (ft_strncmp(command, "echo", 5) == 0)
		ft_echo(cmd->argv);
	else if (ft_strncmp(command, "cd", 3) == 0)
		ft_cd(cmd->argv);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(command, "export", 7) == 0)
		ft_export(sh, cmd->argv);
	else if (ft_strncmp(command, "unset", 6) == 0)
		ft_unset(sh, cmd->argv);
	else if (ft_strncmp(command, "env", 4) == 0)
		ft_env(sh, cmd->argv);
	else if (ft_strncmp(command, "exit", 5) == 0)
		g_shell_sig = 127;
	else
		return (0);
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	char	*command;

	if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL)
		return (0);
	command = cmd->argv[0];
	if (ft_strncmp(command, "echo", 5) == 0 || \
		ft_strncmp(command, "cd", 3) == 0 || \
		ft_strncmp(command, "pwd", 4) == 0 || \
		ft_strncmp(command, "export", 7) == 0 || \
		ft_strncmp(command, "unset", 6) == 0 || \
		ft_strncmp(command, "env", 4) == 0 || \
		ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}
