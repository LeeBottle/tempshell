#include "../minishell.h"

char	*ft_pwd(t_shell *sh, t_token *input)
{
	char	*temp;
	char	*result;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("minishell: pwd");
		sh->last_status = 1;
		return (NULL);
	}
	result = ft_strjoin(temp, "\n");
	free(temp);
	sh->last_status = 0;
	return (result);
}