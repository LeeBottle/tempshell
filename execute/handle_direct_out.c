/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_direct_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:28:02 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:28:02 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	outfile_fd(char *outfile)
{
	int	fd;

	if (outfile)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			perror(outfile);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	append_fd(char *append)
{
	int	fd;

	if (append)
	{
		fd = open(append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			perror(append);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
