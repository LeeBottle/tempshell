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
