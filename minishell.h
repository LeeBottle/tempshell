#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

extern volatile sig_atomic_t shell_sig;

// < > << >>
typedef enum e_toktype {
	TOK_WORD,
    TOK_PIPE,
    TOK_STDIN,
    TOK_STDOUT,
    TOK_HEREDOC,
    TOK_APPEND,
}	t_toktype;
//   '' ""
typedef enum e_quote {
    Q_NONE,
    Q_SINGLE,
    Q_DOUBLE
}	t_quote;

typedef struct s_token {
    char        *val;
    t_toktype   type;
    t_quote     quote;
    struct s_token *next;
}   t_token;

typedef struct s_shell {
    int		last_status;
    char	**envp;
}   t_shell;

int		main();
void	sigint_handler(int sig);
void	init_signal(void);
void	parsing(t_shell *sh, char *input);
t_token *split_value(const char *line);
void	split_pipe(const char **line, t_token **head, t_token **tail);
void	split_redir(const char **line, t_token **head, t_token **tail);
void	split_word(const char **line, t_token **head, t_token **tail);
int		quoted_segment(const char **line, char **acc, t_quote *qsummary);
int     validate_syntax(t_shell *sh, t_token *t);
void	execute(t_shell *sh, t_token *input);
void	ft_echo(t_shell *sh, char **input);
int		is_space(char c);
int		is_quote(char c);
int		is_meta(char c);
void	free_tokens(t_token *t);

#endif