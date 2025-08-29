#include "../minishell.h"

void sigint_handler(int sig)
{
    shell_sig = 1;
	write(0, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    init_signal(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}