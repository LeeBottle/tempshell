#include "minishell.h"

volatile sig_atomic_t	shell_sig;

static void	pre_processing(t_shell *sh, char **envp)
{
	sh->envp = copy_envp(envp);
	shell_sig = 0;
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
	return (shell_sig);
}
