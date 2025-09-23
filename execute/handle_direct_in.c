#include "../minishell.h"

int	infile_fd(char *infile)
{
	int	fd;

	if (infile)
	{
		fd = open(infile, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			perror(infile);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	heredoc_fd(int heredoc_fd)
{
	if (heredoc_fd >= 0)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	return (0);
}
