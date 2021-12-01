#include "minishell.h"

static int	run_child_pipe_commands(t_minishell *msh, t_cmd *cmd, int i, int pipefd[cmd->pipe_count][2])
{
	char	**pipe_args;
	size_t	j;

	j = -1;
	while (++j < cmd->pipe_count)
	{
		if (j != i)
			close(pipefd[j][1]);
		if (j != i - 1)
			close(pipefd[j][0]);
	}
	pipe_args = parse_pipe_part(cmd->args, i);
	if (i == 0)
		return (run_pipein_process(msh, cmd, &pipe_args, pipefd[i]));
	else if (i == cmd->pipe_count)
	{
		redirect_pipeout(pipefd[i - 1]);
		return (run_pipeout_process(msh, cmd, &pipe_args));
	}
	else
	{
		redirect_pipe(pipefd[i - 1], pipefd[i]);
		return (run_pipe_process(msh, cmd, &pipe_args));
	}
	return (0);
}
static int	open_pipeline(t_cmd *cmd, int pipefd[cmd->pipe_count][2])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cmd->pipe_count)
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
	//fprintf(stderr, "pipe opend, pipe_count is %d\n", cmd->pipe_count);
	return (0);
}

static int	wait_pipeline_child(t_minishell *msh, t_cmd *cmd, pid_t pipe_pids[cmd->pipe_count + 1], int pipe_count)
{
	size_t	i;
	int	wstatus;

	i = 0;
	while (i < pipe_count + 1)
	{
		waitpid(pipe_pids[i], &wstatus, 0);
		if (i == pipe_count && WEXITSTATUS(wstatus))
		{
			//fprintf(stderr, "run pipe command wstatus=%d\n", WEXITSTATUS(wstatus));
			return (WEXITSTATUS(wstatus));
		}
		i++;
	}
	return (0);
}

int	run_pipe_commands(t_minishell *msh, t_cmd *cmd, int pipe_count)
{
	pid_t	pipe_pids[pipe_count + 1];
	size_t	i;
	size_t	j;
	int	wstatus;
	int	pipefd[pipe_count][2];

	if (open_pipeline(cmd, pipefd) == 1)
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
			if (run_child_pipe_commands(msh, cmd, i, pipefd) == 1)
			{
				if (msh->ret != NULL)
				{
					printf("pipe cmd:%s\n", msh->ret);
					ft_memdel(&msh->ret);
				}
			//	fprintf(stderr, "exit status in run pipe command=%d\n", msh->exit_status);
				free_msh(msh, 1);
				exit (msh->exit_status);
			}
			return (0);
		}
	}
	j = 0;
	while (j < pipe_count)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
/*
	while (j < pipe_count)
	{
		if (j != pipe_count)
			close(pipefd[j][0]);
		if (j != 0)
			close(pipefd[j][1]);
		j++;
	}
	close(pipefd[0][1]);
	close(pipefd[pipe_count - 1][0]);
*/
	return (wait_pipeline_child(msh, cmd, pipe_pids, pipe_count));
/*
	i = 0;
	while (i < pipe_count + 1)
	{
		waitpid(pipe_pids[i], &wstatus, 0);
		if (i == pipe_count && WEXITSTATUS(wstatus))
		{
			fprintf(stderr, "run pipe command wstatus=%d\n", WEXITSTATUS(wstatus));
			return (WEXITSTATUS(wstatus));
		}
		i++;
	}
	fprintf(stderr, "chile processes done\n");
	return (0);
*/
}
