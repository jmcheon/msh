/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 13:47:25 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/04 13:47:25 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# include "libft.h"

# define HEREDOC_PATH "/tmp/sh-thd."
# define Q_SINGLE '\''
# define Q_DOUBLE '\"'

extern int	g_exit_status;

typedef struct s_flags
{
	int	q_single;
	int	q_double;
}	t_flags;

typedef struct s_cmd
{
	char	*line;
	char	**args;
	char	*temp_path;
	char	**heredoc_paths;
	int		pipe_count;
	int		valid_fd;
}	t_cmd;

typedef struct s_minishell
{
	char	*ret;
	char	**envp;
	int		stdfd[2];
	int		cmd_count;
	t_cmd	*cmd;
}	t_minishell;

/* init & free */
void	init_flags(t_flags *flags);
void	init_cmd(t_cmd *cmd);
void	init_msh(t_minishell *msh, char **envp);
void	free_cmd(t_cmd *cmd, int mode);
void	free_msh(t_minishell *msh, int mode);

/* check validation */
int		check_readline(t_minishell *msh, char **line);
int		run_readline(t_minishell *msh);
char	**check_valid_readline(t_minishell *msh, char *line);
int		check_quotes(t_minishell *msh, char **line);
int		check_pipeline(t_minishell *msh, char **line);
size_t	check_readline_argc(char *line);
char	**check_valid_redirection(t_minishell *msh, t_cmd *cmd, char **args);
size_t	check_pipe_count(char **args, size_t size);

/* parse variables */
void	check_variables(t_minishell *msh, char ***args);
char	*replace_variables(t_minishell *msh, char *line);
char	*replace_variables_one_line(t_minishell *msh, char *line);
int		search_one_variable_path(t_minishell *msh, char *variable);
char	*search_one_variable(t_minishell *msh, char *variable);

/* quotes parsing */
size_t	check_single_quote(char *line, size_t i);
size_t	check_double_quote(char *line, size_t i);
void	check_quote_characters(t_flags *flags, char *line, size_t i);
int		check_readline_quotes(char **temp, char *line);
char	*omit_quotes(char *str);

/* to parse strings */
int		ft_readline(t_minishell *msh);
char	**split_readline_by_argc(char **args, char *line);
char	*rmalloc_line(char *line, size_t size);
size_t	get_new_line_size(char *line);
char	**split_character(char **args, int c);
char	**split_string(char **args, char *s);

/* to parse each part of pipe commands by index */
char	**parse_pipe_part(char **args, int process_num);

/* to parse redirection part */
void	parse_redirection_part(t_minishell *msh, t_cmd *cmd, char ***pipe_args);

/* to run commands */
int		run_one_command(t_minishell *msh, t_cmd *cmd);
int		run_pipe_commands(t_minishell *msh, t_cmd *cmd, int pipe_count);
int		run_child_pipe_commands(t_minishell *msh, t_cmd *cmd,
			int i, int (*pipefd)[2]);

/* to run each process */
int		run_one_process(t_minishell *msh, t_cmd *cmd);
int		run_pipein_process(t_minishell *msh, t_cmd *cmd,
			char ***pipe_args, int pipefd[2]);
int		run_pipe_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args);
int		run_pipeout_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args);

/* to execute one command */
int		execute_one_command(t_minishell *msh, t_cmd *cmd, char **args);
int		ft_execve(t_minishell *msh, char **args);

/* syntax error handling */
int		check_syntax_error(t_minishell *msh, char **args, size_t size);
int		check_readline_syntax_error(t_minishell *msh, char *line);
int		execute_syntax_error(t_minishell *msh, char *s, int i);

/* redirection */
int		execute_heredoc(t_minishell *msh, t_cmd *cmd, char **args);
int		redirect_input(t_minishell *msh, char **args);
int		redirect_output(t_minishell *msh, char *token, char *outfile_path);

void	redirect_pipein(int pipefd[2]);
void	redirect_pipe(int prevfd[2], int pipefd[2]);
void	redirect_pipeout(int pipefd[2]);

/* to parse redirection part */
char	**ft_substr_2dim(char ***args, size_t start, size_t len);
char	**check_redirection_variable(t_minishell *msh, t_cmd *cmd, char **args);

/* funtions */
void	print_2dim_string(char **s, size_t size);
void	print_err_msg(char *msg, char *str, char *msg2);
char	*ft_itos(int c);
int		ft_issymbol(char **s);
int		ft_iscommand(char **s);
size_t	check_command(char ***args);
size_t	check_redirection_input(char **args);
char	*ft_strdup_by_index(char *line, size_t start, size_t end);
char	**malloc_args(char *str);
char	**malloc_args_memdel(char *str);
char	*malloc_by_size(size_t size);
char	**ft_strtrim_2dim(const char **args, const char *set);
char	**ft_strtrim_2dim_by_index(const char **args, size_t start, size_t end);

/* builtin */
int		ft_env(t_minishell *msh);
int		ft_pwd(void);
int		ft_cd(t_minishell *msh, char **args, int err);
int		ft_echo(char **cmd);
int		ft_export(t_minishell *msh, char **args);
int		ft_exit(t_minishell *msh, char **args);
int		ft_exit_pipe(t_minishell *msh, char **args);
int		ft_unset(t_minishell *msh, char **args);
void	ft_setenv(t_minishell *msh, char *path, char *var, char *value);

/* signals */
void	listen_signals_heredoc(void);
void	listen_signals(void);
void	listen_signals_child(void);
void	handle_child_signal(int signum);
void	handle_heredoc(int signum);
void	handle_sigint(int signum);

#endif
