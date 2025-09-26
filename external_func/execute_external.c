/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:26:09 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 19:17:41 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *resolve_cmd_path(t_shell *sh, t_cmd *cmd, int *is_path_search)
{
	char *path;

	*is_path_search = 0;
	if (ft_strchr(cmd->argv[0], '/'))
		path = cmd->argv[0];
	else
	{
		path = get_cmd_path(cmd->argv[0], sh->envp);
		*is_path_search = 1;
	}
	return path;
}

static void error_print_path(t_shell *sh, t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tokens(sh->tokens);
	free_cmds(sh->cmds);
	free_envp(sh->envp);
	exit(127);
}

static void error_print_handle(t_shell *sh, t_cmd *cmd, char *path, int is_path_search)
{
	perror(cmd->argv[0]);
	if (is_path_search)
		free(path);
	free_tokens(sh->tokens);
	free_cmds(sh->cmds);
	free_envp(sh->envp);
	exit(126);
}

void	execute_external(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	int		is_path_search;

	path = resolve_cmd_path(sh, cmd, &is_path_search);
	if (!path)
		error_print_path(sh, cmd);
	execve(path, cmd->argv, sh->envp);
	error_print_handle(sh, cmd, path, is_path_search);
}