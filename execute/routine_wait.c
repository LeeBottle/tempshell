/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:28:07 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:28:08 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_signal_status(int status, int *first_signal, int is_pipeline)
{
	if (WTERMSIG(status) == SIGINT)
	{
		if (is_pipeline)
			g_shell_sig = 0;
		else
			g_shell_sig = 130;
		if (*first_signal)
			ft_putstr_fd("\n", 2);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		if (is_pipeline)
			g_shell_sig = 0;
		else
		{
			g_shell_sig = 131;
			if (*first_signal)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
	}
	*first_signal = 0;
}

static void	handle_exit_status(pid_t waited_pid, pid_t last_pid, int status)
{
	if (waited_pid == last_pid && WIFEXITED(status))
		g_shell_sig = WEXITSTATUS(status);
}

void	wait_processes(pid_t last_pid, int is_pipeline)
{
	int		status;
	pid_t	waited_pid;
	int		first_signal;

	first_signal = 1;
	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid <= 0)
			break ;
		if (WIFSIGNALED(status))
			handle_signal_status(status, &first_signal, is_pipeline);
		else
			handle_exit_status(waited_pid, last_pid, status);
	}
}
