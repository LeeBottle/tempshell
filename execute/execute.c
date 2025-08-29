#include "../minishell.h"


void	execute(t_shell *sh, t_token *input)
{
	char	*return_value;

	return_value = NULL;
	if (input == NULL)
		return ;
	while (input)
	{
		if (ft_strncmp(input->val, "echo", 5) == 0 && input->type == TOK_WORD)
			return_value = ft_echo(sh, input);
		else if (ft_strncmp(input->val, "cd", 3) == 0 && input->type == TOK_WORD)
			ft_cd(sh, input);
		else if (ft_strncmp(input->val, "pwd", 4) == 0 && input->type == TOK_WORD)
			return_value = ft_pwd(sh, input);
		else if (ft_strncmp(input->val, "export", 7) == 0 && input->type == TOK_WORD)
			return_value = ft_export(sh, input);
		else if (ft_strncmp(input->val, "unset", 6) == 0 && input->type == TOK_WORD)
			ft_unset(sh, input);
		else if (ft_strncmp(input->val, "env", 4) == 0 && input->type == TOK_WORD)
			ft_env(sh);
		else if (ft_strncmp(input->val, "exit", 5) == 0 && input->type == TOK_WORD)
			ft_exit(sh);
		else
			sh->last_status = 127;
		input = input->next;
	}
	if (return_value)
	{
		ft_putstr_fd(return_value, 1);
		free(return_value);
	}
}
