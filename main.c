#include "minishell.h"

volatile sig_atomic_t shell_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	sh;
    
	sh.last_status = 0;
    sh.envp = copy_envp(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	shell_sig = 0;
	while (1)
	{
		if (shell_sig)
        {
            shell_sig = 0;
        }
		input = readline("minishell$ ");
		if (!input)
        {
            printf("exit\n");
            break;
        }
		if (*input)
		{
			add_history(input);
			parsing(&sh, input);
		}
		free(input);
	}
	free_envp(sh.envp);
	return (shell_sig);
}
