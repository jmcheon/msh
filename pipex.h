/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:25:57 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/09/12 12:37:11 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "./libft.h"
# include "./get_next_line_bonus.h"
# include "minishell.h"

extern char	**environ;

typedef struct s_pipe
{
	char				*cmd;
	int					pipefd[2];
	struct s_pipe		*prev;
	struct s_pipe		*next;
}	t_pipe;

typedef struct s_pipeline
{
	char				*infile_path;
	char				*outfile_path;
	int					valid_infile;
	int					infile;
	int					outfile;
	t_pipe				*pipe_head;
}	t_pipeline;

int			open_outfile(char *infile_path, char *outfile_path, int *outfile);
int			open_infile(char *path, int *infile);
int			open_infile_bonus(char *path, int *infile);
char		*ft_pipe_out(int argc, char **argv, int pipefd[2], int outfile);
char		*ft_pipe_in(char **argv, int pipefd[2], int infile);

char		*ft_pipeline_infile(t_pipeline *pipeline, t_pipe *pipe);
char		*ft_pipeline_inout(t_pipe *pipe);
char		*ft_pipeline_outfile(t_pipeline *pipeline, t_pipe *pipe);
char		*ft_pipeline_here_doc(t_pipe *pipe, int pipe_here_doc[2]);
int			execute_commands(t_pipeline *pipeline);
int			execute_here_doc_commands(t_pipeline *pipeline, char *limiter);
int			execute_here_doc_one_command(t_pipeline *pipeline,
				t_pipe *pipe, int pipe_here_doc[2], int mode);
int			execute_one_command(t_pipeline *pipeline,
				t_pipe *pipe, int mode);
int			parse_here_doc(int pipe_here_doc[2], char *limiter);

int			check_error_message(char *ret);
char		*ft_error_message_exit(char *ret, char *str, char **args);
void		ft_execve(char *cmd, char **args, char **ret);

t_pipe		*pipe_create_new(char *cmd);
void		pipeline_free(t_pipeline *pipeline);
void		pipe_free(t_pipe **lst);
void		pipe_print(t_pipe **lst);
void		pipe_add_front(t_pipe **lst, t_pipe *new);
int			init_pipe(t_pipe **pipe_head, int argc,
				char **argv, int here_doc);
void		init_pipeline(t_pipeline *pipeline, int argc, char **argv);

#endif
