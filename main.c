/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:26:56 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 17:26:57 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_shell_sig;

static void	pre_processing(t_shell *sh, char **envp)
{
	sh->envp = copy_envp(envp);
	g_shell_sig = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static int	main_loop(t_shell *sh)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (parsing(sh, input))
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	pre_processing(&sh, envp);
	main_loop(&sh);
	free_envp(sh.envp);
	rl_clear_history();
	return (g_shell_sig);
}
