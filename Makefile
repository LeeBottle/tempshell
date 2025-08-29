NAME = 	minishell
CC = cc
CFLAGS =
LIBS = -lreadline
SRCS = main.c\
	signal/init_signal.c\
	parsing/parsing.c\
	parsing/split.c\
	parsing/split_pipe.c\
	parsing/split_redirection.c\
	parsing/split_word.c\
	parsing/split_word_append.c\
	parsing/split_word_append2.c\
	parsing/validate_syntax.c\
	parsing/pipe_end.c\
	execute/execute.c\
	builtin_func/builtin_echo.c\
	builtin_func/builtin_cd.c\
	builtin_func/builtin_pwd.c\
	builtin_func/builtin_export.c\
	builtin_func/builtin_export2.c\
	builtin_func/builtin_unset.c\
	builtin_func/builtin_env.c\
	builtin_func/builtin_exit.c\
	builtin_func/builtin_std.c\
	utils.c

LIBFTDIR = ./libft
LIBFTFILE = libft.a
LIBFT = $(LIBFTDIR)/$(LIBFTFILE)


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
