#include "../minishell.h"

static void	sort_envp(char **envp_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strcmp(envp_copy[j], envp_copy[j + 1]) > 0)
			{
				temp = envp_copy[j];
				envp_copy[j] = envp_copy[j + 1];
				envp_copy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	*print_list(char **envp_copy, int count, char *result)
{
	int		i;
	char	*temp_str;
	char	*key;
	char	*value;
	char	*equal_sign;

	i = 0;
	while (i < count)
	{
		equal_sign = ft_strchr(envp_copy[i], '=');
		temp_str = ft_strjoin(result, "declare -x ");
		free(result);
		result = temp_str;
		if (equal_sign)
		{
			key = ft_substr(envp_copy[i], 0, equal_sign - envp_copy[i]);
			value = equal_sign + 1;
			temp_str = ft_strjoin(result, key);
			free(result);
			result = temp_str;
			free(key);
			temp_str = ft_strjoin(result, "=\"");
			free(result);
			result = temp_str;
			temp_str = ft_strjoin(result, value);
			free(result);
			result = temp_str;
			temp_str = ft_strjoin(result, "\"");
			free(result);
			result = temp_str;
		}
		else
		{
			temp_str = ft_strjoin(result, envp_copy[i]);
			free(result);
			result = temp_str;
		}
		temp_str = ft_strjoin(result, "\n");
		free(result);
		result = temp_str;
		i++;
	}
	return (result);
}

char *export_list(t_shell *sh)
{
	char	*result;
	char	**envp_copy;
	int		i;
	int		count;

	count = 0;
	while (sh->envp[count])
		count++;
	envp_copy = malloc(sizeof(char *) * (count + 1));
	if (!envp_copy)
		return (ft_strdup(""));
	i = 0;
	while (i < count)
	{
		envp_copy[i] = sh->envp[i];
		i++;
	}
	envp_copy[i] = NULL;
	sort_envp(envp_copy, count);
	result = ft_strdup("");
	result = print_list(envp_copy, count, result);
	free(envp_copy);
	sh->last_status = 0;
	return (result);
}
