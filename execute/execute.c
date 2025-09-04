#include "../minishell.h"

void    execute(t_shell *sh, t_token *input)
{
    t_token *current_token;
    int     stdin_backup;
    int     stdout_backup;
    int     fd;
	int		redir_failed;

    if (input == NULL)
        return ;
	redir_failed = 0;
    stdin_backup = dup(STDIN_FILENO);
    stdout_backup = dup(STDOUT_FILENO);
    current_token = input;
   	while (current_token)
	{
		if (current_token->type == TOK_STDIN)
		{
			if (ft_stdin(sh, current_token, stdin_backup, stdout_backup) != 0)
			{
                redir_failed = 1;
                break;
            }
		}
		else if (current_token->type == TOK_STDOUT)
		{
			if (ft_stdout(sh, current_token, stdin_backup, stdout_backup) != 0)
			{
                redir_failed = 1;
                break;
            }
		}
		else if (current_token->type == TOK_APPEND)
		{
			if (ft_append(sh, current_token, stdin_backup, stdout_backup) != 0)
			{
                redir_failed = 1;
                break;
            }
		}
		current_token = current_token->next;
	}
	if (!redir_failed)
	{
		current_token = input;
		while (current_token)
		{
			if (current_token->type == TOK_WORD)
			{
				if (ft_strncmp(current_token->val, "echo", 5) == 0)
					ft_echo(sh, current_token);
				else if (ft_strncmp(current_token->val, "cd", 3) == 0)
					ft_cd(sh, current_token);
				else if (ft_strncmp(current_token->val, "pwd", 4) == 0)
					ft_pwd(sh, current_token);
				else if (ft_strncmp(current_token->val, "export", 7) == 0)
					ft_export(sh, current_token);
				else if (ft_strncmp(current_token->val, "unset", 6) == 0)
					ft_unset(sh, current_token);
				else if (ft_strncmp(current_token->val, "env", 4) == 0)
					ft_env(sh);
				else if (ft_strncmp(current_token->val, "exit", 5) == 0)
					ft_exit(sh);
				else
					sh->last_status = 127;
				break;
			}
			current_token = current_token->next;
		}
	}
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdin_backup);
    close(stdout_backup);
}
