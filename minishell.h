/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:24:19 by byeolee           #+#    #+#             */
/*   Updated: 2025/09/26 19:17:23 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern volatile sig_atomic_t	g_shell_sig;

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
	char			**argv;
	char			*infile;
	char			*outfile;
	char			*append;
	int				in_type;
	int				out_type;
	int				heredoc_fd;
	int				heredoc_interrupted;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token {
	char			*val;
	t_toktype		type;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list {
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef struct s_shell {
	char	**envp;
}	t_shell;

int		main(int argc, char **argv, char **envp);
void	sigint_handler(int sig);
void	init_signal(void);
void	heredoc_sigint(int signo);
int		is_space(char c);
int		is_quote(char c);
int		is_meta(char c);
void	free_split(char **arr);
void	free_tokens(t_token *t);

//parsing
int		parsing(t_shell *sh, char *input);
void	free_cmds(t_cmd *head);
t_token	*split_value(t_shell *sh, char *line);
void	split_pipe(char **line, t_token_list *list);
void	split_redir(char **line, t_token_list *list);
void	split_word(t_shell *sh, char **line, t_token_list *list);
void	env_append(char **acc, t_token_list *list, char **parts);
void	process_character(t_shell *sh, char **line, char **acc, \
		t_token_list *list);
void	append_expanded_val(char **acc, char *expanded_val);
void	word_node(t_token_list *list, char *acc);
void	heredoc_parent_close(pid_t pid, int status, \
		struct termios term_backup, t_cmd *cmd);
char	*get_expanded_value(t_shell *sh, char **line);
int		validate_syntax(t_token *t);
int		pipe_end(t_shell *sh, t_token **t_head);
t_cmd	*token_to_cmd(t_token *tokens);
t_cmd	*start_new_cmd(t_cmd **head, t_cmd **tail);
void	handle_heredoc(t_cmd *cmd, char *limiter);
void	append_argv(t_cmd *cmd, char *val);
void	heredoc_child(char *limiter, int write_fd);
void	handle_unclosed_quote(char **acc);

//execute
int		execute(t_shell *sh, t_cmd *cmd);
int		outfile_checker(t_cmd *cmds);
void	process_cmd(t_shell *sh, t_cmd *cmds, int *pv_pipe, pid_t *last_pid);
void	wait_processes(pid_t last_pid, int is_pipeline);
void	is_direct(t_shell *sh, t_cmd *cmds);
int		handle_redirections(t_cmd *cmd);
int		infile_fd(char *infile);
int		heredoc_fd(int heredoc_fd);
int		outfile_fd(char *outfile);
int		append_fd(char *append);
int		func_builtin(t_shell *sh, t_cmd *cmd);
int		is_builtin(t_cmd *cmd);

//builting_func
void	ft_echo(char **argv);
void	ft_cd(char **argv);
void	ft_pwd(void);
void	ft_export(t_shell *sh, char **argv);
void	export_list(t_shell *sh);
void	export_key_only(t_shell *sh, char **argv, int i);
void	add_key_only(t_shell *sh, char *key);
void	export_val(t_shell *sh, char **argv, int i, int j);
void	append_val(t_shell *sh, char **argv, int i, int j);
void	add_new_env(t_shell *sh, char *key, char *value);
int		key_chekcer(char *key);
void	export_error(char *argv);
void	ft_unset(t_shell *sh, char **argv);
void	ft_env(t_shell *sh, char **argv);
char	**copy_envp(char **envp);
void	free_envp(char **envp);
int		ft_exit(t_cmd *cmds);

//external_func
void	execute_external(t_shell *sh, t_cmd *cmd);
char	*get_cmd_path(char *cmd, char **env);

#endif
