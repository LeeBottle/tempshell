/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   routine_cmd.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: byeolee <byeolee@student.42gyeongsan.kr	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/26 17:28:10 by byeolee		   #+#	#+#			 */
/*   Updated: 2025/09/26 18:36:35 by byeolee		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"
/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* routine_cmd.c                                      :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/09/26 17:28:10 by byeolee           #+#    #+#             */
/* Updated: 2025/09/26 17:28:10 by byeolee          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_exit(t_shell *sh, int exit_code)
{
	free_tokens(sh->tokens);
	free_cmds(sh->cmds_head);
	free_envp(sh->envp);
	exit(exit_code);
}

static void	child_process(t_shell *sh, t_cmd *cmd, int fd[2], int pv_pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pv_pipe != -1)
	{
		dup2(pv_pipe, STDIN_FILENO);
		close(pv_pipe);
	}
	if (cmd->next != NULL)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (handle_redirections(cmd))
		child_exit(sh, 1);
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
		child_exit(sh, 0);
	if (func_builtin(sh, cmd))
		child_exit(sh, g_shell_sig);
	else
		execute_external(sh, cmd);
}

static void	parent_process(int fd[2], int *pv_pipe, t_cmd *cmd)
{
	if (*pv_pipe != -1)
		close(*pv_pipe);
	if (cmd->next != NULL)
	{
		close(fd[1]);
		*pv_pipe = fd[0];
	}
	if (cmd->in_type == 1 && cmd->heredoc_fd >= 0)
		close(cmd->heredoc_fd);
}

void	process_cmd(t_shell *sh, int *pv_pipe, pid_t *last_pid)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*current_cmd;

	current_cmd = sh->cmds_head;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL && pipe(fd) == -1)
		{
			perror("minishell: pipe");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			return ;
		}
		else if (pid == 0)
			child_process(sh, current_cmd, fd, *pv_pipe);
		parent_process(fd, pv_pipe, current_cmd);
		*last_pid = pid;
		current_cmd = current_cmd->next;
	}
}
