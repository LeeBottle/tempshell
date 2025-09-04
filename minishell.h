#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

extern volatile sig_atomic_t shell_sig;

// < > << >>
typedef enum e_toktype {
	TOK_WORD,
    TOK_PIPE,
	TOK_HEREDOC_WORD,
    TOK_STDIN,
    TOK_STDOUT,
    TOK_HEREDOC,
    TOK_APPEND,
}	t_toktype;

typedef struct s_cmd {
	char	**argv; //명령+인자
	char	*infile; // <
	char	*outfile; // >
	char	*append; // >>
    t_list *heredoc; // << 내용물
	struct s_cmd *next;
}	t_cmd;

typedef struct s_token {
    char        *val;
    t_toktype   type;
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
t_token *split_value(t_shell *sh, char *line);
void	split_pipe(char **line, t_token **head, t_token **tail);
void	split_redir(char **line, t_token **head, t_token **tail);
void	split_word(t_shell *sh, char **line, t_token **head, t_token **tail);\
void	process_character(t_shell *sh, char **line, char **acc);
void	append_expanded_val(char **acc, char *expanded_val);
char	*get_expanded_value(t_shell *sh, char **line);
int     validate_syntax(t_shell *sh, t_token *t);
int		pipe_end(t_shell *sh, t_token **t_head);
void	execute(t_shell *sh, t_token *input);
int		ft_stdin(t_shell *sh, t_token *token, int stdin_bkp, int stdout_bkp);
int		ft_stdout(t_shell *sh, t_token *token, int stdin_bkp, int stdout_bkp);
int		ft_append(t_shell *sh, t_token *token, int stdin_bkp, int stdout_bkp);
void	ft_echo(t_shell *sh, t_token *input);
void	ft_cd(t_shell *sh, t_token *input);
void	ft_pwd(t_shell *sh, t_token *input);
void	ft_export(t_shell *sh, t_token *input);
void	export_list(t_shell *sh);
void	ft_unset(t_shell *sh, t_token *input);
void	ft_env(t_shell *sh);
void	ft_exit(t_shell *sh);
int		is_space(char c);
int		is_quote(char c);
int		is_meta(char c);
void    ft_env(t_shell *sh);
char    **copy_envp(char **envp);
void    free_envp(char **envp);
void	free_tokens(t_token *t);
t_cmd	*token_to_cmd(t_token *tokens);
static void	pros_token(t_cmd **cmd, t_cmd **head, t_cmd **tail, t_token **cur);
t_cmd	*start_new_cmd(t_cmd **head, t_cmd **tail);
static void	handle_redir(t_cmd *cmd, t_token *tok);
void handle_heredoc(t_cmd *cmd, char *limiter);
void	append_argv(t_cmd *cmd, char *val);
void	print_cmds(t_cmd *head);
void handle_heredoc(t_cmd *cmd, char *limiter);//아래부턴 테스트
static void heredoc_child(t_cmd *cmd, char *limiter);

#endif