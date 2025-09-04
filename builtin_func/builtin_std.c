#include "../minishell.h"

static void restore_fd(int stdin_backup, int stdout_backup)
{
    dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
}

int	ft_stdin(t_shell *sh, t_token *token, int stdin_bkp, int stdout_bkp)
{
    int fd;

	token = token->next;
    if (!token)
        return (0);
    fd = open(token->val, O_RDONLY);
    if (fd < 0)
    {
        perror("minishell");
        sh->last_status = 1;
        restore_fd(stdin_bkp, stdout_bkp);
        return (1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
	return (0);
}

int	ft_stdout(t_shell *sh, t_token *token, int stdin_bkp, int stdout_bkp)
{
    int fd;

	token = token->next;
    if (!token)
        return (0);
    fd = open(token->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("minishell");
        sh->last_status = 1;
        restore_fd(stdin_bkp, stdout_bkp);
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
	return (0);
}

int	ft_append(t_shell *sh, t_token *token, int stdin_bkp, int stdout_bkp)
{
    int fd;

	token = token->next;
    if (!token)
        return (0);
    fd = open(token->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("minishell");
        sh->last_status = 1;
        restore_fd(stdin_bkp, stdout_bkp);
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
	return (0);
}
