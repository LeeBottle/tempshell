#include "minishell.h"

volatile sig_atomic_t shell_sig = 0;

int	main(void)
{
	char	*input;
	t_shell	sh;

	sh.last_status = 0;
    sh.envp = NULL;
	init_signal();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (shell_sig == SIGINT)
		{
            sh.last_status = 130;
            shell_sig = 0;
            free(input);
            continue;
        }
		if (*input)
		{
			add_history(input);
			parsing(&sh, input);
		}
		free(input);
	}
	return (shell_sig);
}

