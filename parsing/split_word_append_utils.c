/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_append_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejo <sejo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:55:24 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 15:50:22 by sejo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_append(char **acc, t_token_list *list, char **parts)
{
	int	i;

	if (*acc)
	{
		append_expanded_val(acc, parts[0]);
		word_node(list, *acc);
		*acc = NULL;
	}
	else
		*acc = ft_strdup(parts[0]);
	i = 1;
	while (parts[i])
	{
		if (*parts[i])
			word_node(list, ft_strdup(parts[i]));
		i++;
	}
}

void	handle_unclosed_quote(char **acc)
{
	if (*acc)
	{
		free(*acc);
		*acc = NULL;
	}
	ft_putendl_fd("double quote error", 2);
}
