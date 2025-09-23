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
    int		in_type; // 1 heredoc , 0 infile , -1 없음
	int		out_type; // 1 append , 0 outfile, -1 없음
    int     heredoc_fd; // << 내용물
    int		heredoc_interrupted;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_token {
    char        *val;
    t_toktype   type;
    struct s_token *next;
}   t_token;

typedef struct s_shell {
    char	**envp;
}   t_shell;


int		main();
void	sigint_handler(int sig);
void	init_signal(void);
int		parsing(t_shell *sh, char *input); //->int
t_token *split_value(t_shell *sh, char *line);
void	split_pipe(char **line, t_token **head, t_token **tail);
void	split_redir(char **line, t_token **head, t_token **tail);
void	split_word(t_shell *sh, char **line, t_token **head, t_token **tail);
void	process_character(t_shell *sh, char **line, char **acc);
void	append_expanded_val(char **acc, char *expanded_val);
char	*get_expanded_value(t_shell *sh, char **line);
int		validate_syntax(t_shell *sh, t_token *t);
int		pipe_end(t_shell *sh, t_token **t_head);

int	execute(t_shell *sh, t_cmd *cmd); //->int
void	process_cmd(t_shell *sh, t_cmd *cmds, int *pv_pipe, pid_t *last_pid);
void	wait_processes(t_shell *sh, pid_t last_pid);

void	is_direct(t_shell *sh, t_cmd *cmds);
int		handle_redirections(t_cmd *cmd);
int		infile_fd(char *infile);
int		heredoc_fd(int heredoc_fd);
int		outfile_fd(char *outfile);
int		append_fd(char *append);
int		func_builtin(t_shell *sh, t_cmd *cmd);
int		is_builtin(t_cmd *cmd);

void	ft_echo(char **argv);
void	ft_cd(char **argv);
void	ft_pwd(void);
void	ft_export(t_shell *sh, char **argv);
void	export_list(t_shell *sh);
int		key_chekcer(char *key);
void	export_error(char *argv);
void	ft_unset(t_shell *sh, char **argv);
void	ft_env(t_shell *sh, char **argv);
void	ft_exit(char **argv);
void	execute_external(t_shell *sh, t_cmd *cmd);
char	*get_cmd_path(char *cmd, char **env);

int		is_space(char c);
int		is_quote(char c);
int		is_meta(char c);
char	**copy_envp(char **envp);
void	free_envp(char **envp);
void	free_tokens(t_token *t);
void    free_cmds(t_cmd *head);
void	free_split(char **arr);
t_cmd	*token_to_cmd(t_token *tokens);
t_cmd	*start_new_cmd(t_cmd **head, t_cmd **tail);
void	handle_heredoc(t_cmd *cmd, char *limiter);
void	append_argv(t_cmd *cmd, char *val);
void	print_cmds(t_cmd *head);
void	handle_heredoc(t_cmd *cmd, char *limiter); // 중복 선언은 제거 가능

// ** 새로 추가해야 하는 함수 선언들 **
int		handle_heredoc_input(char *limiter, int write_fd);
void	heredoc_sigint(int signo);

#endif
