/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:15:46 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 17:16:46 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	end_is_pipe(t_token *t)
{
	if (!t)
		return (0);
	while (t->next)
		t = t->next;
	if (t->type == TOK_PIPE)
		return (1);
	return (0);
}

static void	pipe_input(char *input, t_token *last, t_shell *sh, t_token *t_head)
{
	t_token	*new_tokens;

	add_history(input);
	new_tokens = split_value(sh, input);
	if (new_tokens)
	{
		last = t_head;
		while (last && last->next)
			last = last->next;
		if (last)
			last->next = new_tokens;
	}
}

int	pipe_end(t_shell *sh, t_token **t_head)
{
	char	*input;
	t_token	*last;

	last = NULL;
	while (end_is_pipe(*t_head))
	{
		input = readline("> ");
		printf("%s / %d\n", input, g_shell_sig);
		if (g_shell_sig == 1)
			return (1);
		if (!input)
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
			ft_putstr_fd("exit\n", 2);
			free_tokens(*t_head);
			*t_head = NULL;
			exit(258);
		}
		if (*input)
		{
			pipe_input(input, last, sh, *t_head);
		}
		free(input);
	}
	return (0);
}
