/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:05:48 by sejo              #+#    #+#             */
/*   Updated: 2025/09/26 18:45:11 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir(t_toktype ty)
{
	return (ty == TOK_STDIN || ty == TOK_STDOUT
		|| ty == TOK_APPEND || ty == TOK_HEREDOC);
}

static const char	*tok_lexeme(t_token *t)
{
	if (!t)
		return ("\\n");
	if (t->type == TOK_STDIN)
		return ("<");
	if (t->type == TOK_STDOUT)
		return (">");
	if (t->type == TOK_APPEND)
		return (">>");
	if (t->type == TOK_HEREDOC)
		return ("<<");
	if (t->val != NULL)
		return (t->val);
	else
		return ("");
}

static int	syntax_error(t_token *t)
{
	write(2, "minishell: parse error near `", 23);
	write(2, tok_lexeme(t), ft_strlen(tok_lexeme(t)));
	write(2, "'\n", 2);
	g_shell_sig = 258;
	return (1);
}

static int	pipe_start_error(void)
{
	write(2, "minishell: syntax error near unexpected token '|'\n", 55);
	g_shell_sig = 2;
	return (1);
}

int	validate_syntax(t_token *t)
{
	t_token	*cur;

	cur = t;
	if (!cur)
		return (0);
	if (cur->type == TOK_PIPE)
		return (pipe_start_error());
	while (cur)
	{
		if (cur->type == TOK_PIPE)
		{
			if (!cur->next || cur->next->type == TOK_PIPE)
				return (syntax_error(cur->next));
		}
		else if (is_redir(cur->type))
		{
			if (!cur->next || cur->next->type != TOK_WORD)
				return (syntax_error(cur->next));
		}
		cur = cur->next;
	}
	return (0);
}
