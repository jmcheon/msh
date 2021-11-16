#include "minishell.h"

void	redirect_pipein(int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

int	run_pipein_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args)
{
	fprintf(stderr, "first process, pipe args size=%zu\n", ft_strlen_2dim((const char **)*pipe_args));
	parse_redirection_part(msh, cmd, pipe_args);
	if (ft_issymbol(&(*pipe_args)[0]) != 0)
	{
		fprintf(stderr, "first process no command with redirection\n");
		ft_memdel_2dim(pipe_args);
		*pipe_args = NULL;
	}
	//if (execute_pipein_command(msh, *pipe_args, pipefd) == 1)
	if (execute_one_command(msh, cmd, *pipe_args) == 1)
	{
		ft_memdel_2dim(pipe_args);
		return (1);
	}
	ft_memdel_2dim(pipe_args);
	fprintf(stderr, "first ps exit 0\n");
/*
	if (msh->heredoc_paths[process_num] != NULL)
	{
		fprintf(stderr, "fisrt ps heredoc path=%s\n", msh->heredoc_paths[process_num]);
		ft_memdel(&msh->heredoc_paths[process_num]);
		free(msh->heredoc_paths[process_num]);
		ft_memdel_2dim(&msh->heredoc_paths);
	}
*/
		
	//free_msh(msh);
	//return (0);
	exit(0);
}

void	redirect_pipeout(int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	run_pipeout_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args)
{
	fprintf(stderr, "last process, pipe args size=%zu\n", ft_strlen_2dim((const char **)*pipe_args));
	parse_redirection_part(msh, cmd, pipe_args);
	if (ft_issymbol(&(*pipe_args)[0]) != 0)
	{
		fprintf(stderr, "last process no command with redirection\n");
		ft_memdel_2dim(pipe_args);
		*pipe_args = NULL;
	}
//	if (execute_pipeout_command(msh, *pipe_args, pipefd) == 1)
	if (execute_one_command(msh, cmd, *pipe_args) == 1)
	{
		ft_memdel_2dim(pipe_args);
		return (1);
	}
	ft_memdel_2dim(pipe_args);
	fprintf(stderr, "last ps exit 0\n");
/*
	if (msh->heredoc_paths[process_num] != NULL)
	{
		fprintf(stderr, "last ps heredoc path=%s\n", msh->heredoc_paths[process_num]);
		ft_memdel(&msh->heredoc_paths[0]);
		ft_memdel(&msh->heredoc_paths[process_num]);
		free(msh->heredoc_paths[process_num]);
		ft_memdel_2dim(&msh->heredoc_paths);
	}
*/
	//free_msh(msh);
	exit(0);
}

void	redirect_pipe(int prevfd[2], int pipefd[2])
{
	close(prevfd[1]);
	dup2(prevfd[0], STDIN_FILENO);
	close(prevfd[0]);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

int	run_pipe_process(t_minishell *msh, t_cmd *cmd, char ***pipe_args)
{
	fprintf(stderr, "pipe process, pipe args size=%zu\n", ft_strlen_2dim((const char **)*pipe_args));
	parse_redirection_part(msh, cmd, pipe_args);
	if (ft_issymbol(&(*pipe_args)[0]) != 0)
	{
		fprintf(stderr, "pipe process no command with redirection\n");
		ft_memdel_2dim(pipe_args);
		*pipe_args = NULL;
	}
	//if (execute_pipe_command(msh, *pipe_args, prevfd, pipefd) == 1)
	if (execute_one_command(msh, cmd, *pipe_args) == 1)
	{
		ft_memdel_2dim(pipe_args);
		return (1);
	}
	ft_memdel_2dim(pipe_args);
	fprintf(stderr, "pipe ps exit 0\n");
/*
	if (msh->heredoc_paths[process_num] != NULL)
	{
		fprintf(stderr, "last ps heredoc path=%s\n", msh->heredoc_paths[process_num]);
		ft_memdel(&msh->heredoc_paths[0]);
		ft_memdel(&msh->heredoc_paths[process_num]);
		free(msh->heredoc_paths[process_num]);
		ft_memdel_2dim(&msh->heredoc_paths);
	}
*/
	//free_msh(msh);
	exit(0);
}
