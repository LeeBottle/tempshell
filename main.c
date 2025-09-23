#include "minishell.h"

volatile sig_atomic_t shell_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	sh;
    
    sh.envp = copy_envp(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
        {
            printf("exit\n");
            break;
        }
		if (*input)
		{
			add_history(input);
			if (parsing(&sh, input))
			{
				free(input);
				break;
			}
		}
		free(input);
	}
	free_envp(sh.envp);
	rl_clear_history();
	return (shell_sig);
}
