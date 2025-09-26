/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:27:40 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:27:41 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("minishell: pwd");
		g_shell_sig = 1;
		return ;
	}
	ft_putstr_fd(temp, 1);
	ft_putstr_fd("\n", 1);
	free(temp);
	g_shell_sig = 0;
}
