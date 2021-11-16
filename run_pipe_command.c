#include "minishell.h"

static int	run_child_pipe_commands(t_minishell *msh, int i, int pipefd[msh->pipe_count][2])
{
	char	**pipe_args;
	size_t	j;

	j = 0;
	while (j < msh->pipe_count)
	{
		if (j != i)
			close(pipefd[j][1]);
		if (j != i - 1)
			close(pipefd[j][0]);
		j++;
	}
	pipe_args = parse_pipe_part_by_index(msh->args, i);
	if (i == 0)
	{
		if (run_pipein_process(msh, &pipe_args, pipefd[i]) == 1)
			return (1);
	}
	else if (i == msh->pipe_count)
	{
		if (run_pipeout_process(msh, &pipe_args, pipefd[i - 1]) == 1)
			return (1);
	}
	else
	{
		if (run_pipe_process(msh, &pipe_args, pipefd[i - 1], pipefd[i]) == 1)
			return (1);
	}
	return (0);
}

static int	open_pipeline(t_minishell *msh, int pipefd[msh->pipe_count][2])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < msh->pipe_count)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe()");
			j = 0;
			while (j < i)
			{
				close(pipefd[j][0]);
				close(pipefd[j][1]);
				j++;
			}
			return (1);
		}
		i++;
	}
	fprintf(stderr, "pipe opend, pipe_count is %d\n", msh->pipe_count);
	return (0);
}

static void	close_pipeline(t_minishell *msh, int pipefd[msh->pipe_count][2])
{
	size_t	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < pipe_count + 1)
	{
		wait(NULL);
		i++;
	}
}

int	run_pipe_commands(t_minishell *msh, int pipe_count)
{
	pid_t	pipe_pids[pipe_count + 1];
	size_t	i;
	int	pipefd[pipe_count][2];

	if (open_pipeline(msh, pipefd) == 1)
		return (1);
	i = -1;
	while (++i < pipe_count + 1)
	{
		pipe_pids[i] = fork();
		if (pipe_pids[i] == -1)
		{
			perror("fork()");
			return (1);
		}
		if (pipe_pids[i] == 0)
		{
			if (run_child_pipe_commands(msh, i, pipefd) == 1)
				return (1);
			return (0);
		}
	}
	close_pipeline(msh, pipefd);
	fprintf(stderr, "chile processes done\n");
/*
	if (msh->temp_path != NULL)
		fprintf(stderr, "ret of unlink=%d\n", unlink(msh->temp_path));
	if (msh->temp_path != NULL)
		fprintf(stderr, "ret of unlink=%d\n", unlink(msh->temp_path));
*/
	return (0);
}
