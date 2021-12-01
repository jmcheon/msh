#include "minishell.h"

int	run_pipein_process(t_minishell *msh,
		t_cmd *cmd, char ***pipe_args, int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	parse_redirection_part(msh, cmd, pipe_args);
	if (ft_issymbol(&(*pipe_args)[0]) != 0)
	{
		ft_memdel_2dim(pipe_args);
		*pipe_args = NULL;
	}
	if (execute_one_command(msh, cmd, *pipe_args) == 1)
	{
		ft_memdel_2dim(pipe_args);
		return (1);
	}
	ft_memdel_2dim(pipe_args);
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
	parse_redirection_part(msh, cmd, pipe_args);
	if (ft_issymbol(&(*pipe_args)[0]) != 0)
	{
		ft_memdel_2dim(pipe_args);
		*pipe_args = NULL;
	}
	if (execute_one_command(msh, cmd, *pipe_args) == 1)
	{
		ft_memdel_2dim(pipe_args);
		return (1);
	}
	ft_memdel_2dim(pipe_args);
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
	parse_redirection_part(msh, cmd, pipe_args);
	if (ft_issymbol(&(*pipe_args)[0]) != 0)
	{
		ft_memdel_2dim(pipe_args);
		*pipe_args = NULL;
	}
	if (execute_one_command(msh, cmd, *pipe_args) == 1)
	{
		ft_memdel_2dim(pipe_args);
		return (1);
	}
	ft_memdel_2dim(pipe_args);
	exit(0);
}
