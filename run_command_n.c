#include "minishell.h"

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
	return (0);
}

static int	wait_pipeline_child(t_minishell *msh,
			t_cmd *cmd, pid_t *pipe_pids, int pipe_count)
{
	size_t	i;
	int		wstatus;

	i = 0;
	while (i < pipe_count + 1)
	{
		waitpid(pipe_pids[i], &wstatus, 0);
		if (i == pipe_count && WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == 2)
				return (130);
			else if (WTERMSIG(wstatus) == 3)
				return (131);
			else
				return (WIFSIGNALED(wstatus));
		}
		if (i == pipe_count && WEXITSTATUS(wstatus))
			return (WEXITSTATUS(wstatus));
		i++;
	}
	return (0);
}

static int	run_pipeline(t_minishell *msh,
			pid_t *pipe_pids, int (*pipefd)[2], size_t i)
{
	while (++i < msh->cmd[0].pipe_count + 1)
	{
		pipe_pids[i] = fork();
		if (pipe_pids[i] == -1)
		{
			perror("fork()");
			return (1);
		}
		listen_signals_child();
		if (pipe_pids[i] == 0)
		{
			if (run_child_pipe_commands(msh, &msh->cmd[0], i, pipefd) == 1)
			{
				if (msh->ret != NULL)
					printf("pipe cmd:%s\n", msh->ret);
				free(pipefd);
				free(pipe_pids);
				free_msh(msh, 1);
				exit (msh->exit_status);
			}
			return (0);
		}
	}
	return (0);
}

static int	open_pipeline_new(t_cmd *cmd, int (*pipefd)[2])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cmd->pipe_count)
	{
		if (pipe((pipefd)[i]) == -1)
		{
			perror("pipe()");
			j = 0;
			while (j < i)
			{
				close((pipefd[j])[0]);
				close((pipefd[j])[1]);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	run_pipe_commands(t_minishell *msh, t_cmd *cmd, int pipe_count)
{
	pid_t	*pipe_pids;
	size_t	i;
	int		ret;
	int		(*pipefd)[2];

	i = 0;
	ret = 0;
	pipefd = (int (*)[2])malloc(sizeof(int) * 2 * pipe_count);
	if (!pipefd)
		return (1);
	pipe_pids = (pid_t *)malloc(sizeof(pid_t) * (pipe_count + 1 + 1));
	if (!pipe_pids)
	{
		free(pipefd);
		return (1);
	}
	if (open_pipeline_new(cmd, (pipefd)) == 1)
	{
		free(pipefd);
		free(pipe_pids);
		return (1);
	}
	if (run_pipeline(msh, pipe_pids, pipefd, -1) == 1)
	{
		free(pipefd);
		free(pipe_pids);
		return (1);
	}
	while (i < pipe_count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	ret = wait_pipeline_child(msh, cmd, pipe_pids, pipe_count);
	free(pipefd);
	free(pipe_pids);
	return (ret);
}
