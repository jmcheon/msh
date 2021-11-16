#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "libft.h"
#include "get_next_line.h"

# define HEREDOC_PATH "/tmp/sh-thd."
# define Q_SINGLE '\''
# define Q_DOUBLE '\"'

typedef struct s_flags
{
	//int	valid_fd;
	//int	redirection_input;
	int	q_single;
	int	q_double;
}	t_flags;

typedef struct s_args
{
	char	**args;
	char	*token;
}	t_args;

typedef struct	s_cmd
{
	char	*line;
	char	**args;
	char	*token;
	char	*temp_path;
	char	**heredoc_paths;
	int	pipe_count;
	int	valid_fd;
	//t_flags	flags;
}	t_cmd;

typedef struct	s_minishell
{
	char	*ret;
	char	**envp;
	int	stdfd[2];
	int	cmd_count;
	t_cmd	*cmd;
}	t_minishell;

/* init & free */
void	init_flags(t_flags *flags);
void	init_cmd(t_cmd *cmd);
void	init_msh(t_minishell *msh, char **envp);
void	free_cmd(t_cmd *cmd);
void	free_msh(t_minishell *msh);

/* check readline */

/* check validation */
int	check_readline(t_minishell *msh, char **line);
int	check_quotes(t_minishell *msh, char **line);
int	check_pipeline(t_minishell *msh, char **line);

size_t	check_readline_argc(char *line);
char	**check_valid_readline(t_minishell *msh, char *line);
char	**check_valid_redirection(t_minishell *msh, t_cmd *cmd, char **args);
size_t	check_pipe_count(char **args, size_t size);

/* quotes parsing */
size_t	check_single_quote(char *line, size_t *argc);
size_t	check_double_quote(char *line, size_t *argc);
void	check_quote_characters(t_flags *flags, char *line);
char	*omit_character(char *str, int c);
char	*omit_quotes(char *str);

/* to parse strings */
int	ft_readline(t_minishell *msh);
char	**split_readline_by_argc(t_minishell *msh, char *line);
char	**split_character(char **args, int c);
char	**split_string(char **args, char *s);

/* to parse each part of pipe commands by index */
char	**parse_pipe_part(char **args, int process_num);

/* to parse redirection part */
void	parse_redirection_part(t_minishell *msh, t_cmd *cmd, char ***pipe_args);

/* to run commands */
int	run_one_command(t_minishell *msh, t_cmd *cmd);
int	run_pipe_commands(t_minishell *msh, t_cmd *cmd, int pipe_count);

/* to run each process */
int	run_one_process(t_minishell *msh, t_cmd *cmd);
int	run_pipein_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args);
int	run_pipe_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args);
int	run_pipeout_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args);

/* to execute one command */
int	execute_one_command(t_minishell *msh, t_cmd *cmd, char **args);
void	ft_execve(t_minishell *msh, char **args);

/* syntax error handling */
int	check_syntax_error(t_minishell *msh, char **args, size_t size);
int	check_readline_syntax_error(t_minishell *msh, char *line);
int	execute_syntax_error(t_minishell *msh, char *s, int i);

/* redirection */
int	execute_heredoc(t_minishell *msh, t_cmd *cmd, char **args);
int	redirect_input(t_minishell *msh, char **args);
int	redirect_output(t_minishell *msh, char *token, char *outfile_path);

void	redirect_pipein(int pipefd[2]);
void	redirect_pipe(int prevfd[2], int pipefd[2]);
void	redirect_pipeout(int pipefd[2]);

/* to parse redirection part */
char	**ft_strtrim_2dim_by_index(char ***args, int start, int num);

/* funtions */
void	print_2dim_string(char **s, size_t size);
char	*ft_itos(int c);
int	ft_issymbol(char **s);
int	ft_iscommand(char **s);
size_t	check_command(char ***args);
size_t	check_redirection_input(char **args);




#endif
