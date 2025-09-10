#include "minishell.h"

volatile sig_atomic_t shell_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**env;
	t_shell	sh;
    
	sh.last_status = 0;
    sh.envp = copy_envp(envp);
	env = copy_envp(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		shell_sig = 0;
		input = readline("minishell$ ");
		if (!input)
        {
            printf("exit\n");
            break;
        }
		if (*input)
		{
			add_history(input);
			parsing(&sh, input, env);
		}
		free(input);
	}
	free_envp(sh.envp);
	return (shell_sig);
}
