#include "minishell.h"

char	**ft_strtrim_2dim_by_index(char ***args, int start, int num)
{
	char	**new_args;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen_2dim((const char **)*args) - num;
	new_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_args)
		return ((char **)NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (j == start)
		{
			while (num > 0)
			{
				num--;
				j++;
			}
		}
		new_args[i++] = ft_strdup((*args)[j++]);
	}
	new_args[i] = NULL;
	ft_memdel_2dim(args);
	return (new_args);
}

void	parse_redirection_part(t_minishell *msh, t_cmd *cmd, char ***pipe_args)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen_2dim((const char **)*pipe_args);
	while (i < size)
	{
		//fprintf(stderr, "i, size = (%zu, %zu)\n", i, size);
		//printf("\ttest pipe_args[%zu]=%s, ret of strcmp=%d\n", i, pipe_args[i], ft_strcmp(pipe_args[i], "<"));
		//printf("\tret of strcmp=%d\n", ft_strcmp(pipe_args[i], "<"));
		if ((!ft_strcmp((*pipe_args)[i], "<")))// || (!ft_strcmp((*pipe_args)[i], "<<")))
		{
			if (redirect_input(msh, *pipe_args + i) == 1)
				cmd->valid_fd = -1;
			//if ((!ft_strcmp((*pipe_args)[i], "<<")))
			//	unlink(msh->temp_path);
			*pipe_args = ft_strtrim_2dim_by_index(pipe_args, i, 2);
			size -= 2;
			i--;
		}
		else if ((!ft_strcmp((*pipe_args)[i], ">")) || (!ft_strcmp((*pipe_args)[i], ">>")))
		{
			if (redirect_output(msh, (*pipe_args)[i], (*pipe_args)[i + 1]) == 1)
				cmd->valid_fd = -1;
			*pipe_args = ft_strtrim_2dim_by_index(pipe_args, i, 2);
			size -= 2;
			i--;
		}
		i++;
	}
	//size = ft_strlen_2dim((const char **)msh->args);
	fprintf(stderr, "$-----parse_redirection_part------$\n");
	print_2dim_string(*pipe_args, ft_strlen_2dim((const char **)*pipe_args));
}

static int	run_child_pipe_commands(t_minishell *msh, t_cmd *cmd, int i, int pipefd[cmd->pipe_count][2])
{
	char	**pipe_args;
	size_t	j;

	j = 0;
	while (j < cmd->pipe_count)
	{
		if (j != i)
			close(pipefd[j][1]);
		if (j != i - 1)
			close(pipefd[j][0]);
		j++;
	}
	pipe_args = parse_pipe_part(cmd->args, i);
	if (i == 0)
	{
		redirect_pipein(pipefd[i]);
		return (run_pipein_process(msh, cmd, &pipe_args));
	}
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
	fprintf(stderr, "pipe opend, pipe_count is %d\n", cmd->pipe_count);
	return (0);
}

int	run_pipe_commands(t_minishell *msh, t_cmd *cmd, int pipe_count)
{
	pid_t	pipe_pids[pipe_count + 1];
	char	**pipe_args;
	size_t	size;
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
				return (1);
			return (0);
		}
		//i++;
	}
	//printf("parent\n");
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
	i = 0;
	while (i < pipe_count + 1)
	{
		//wait_ret = waitpid(pipe_pids[i], NULL, 0);
		//waitpid(pipe_pids[i], NULL, 0);
		wait(&wstatus);
		//wait(NULL);
		i++;
	}
	fprintf(stderr, "chile processes done\n");
/*
	if (msh->temp_path != NULL)
		fprintf(stderr, "ret of unlink=%d\n", unlink(msh->temp_path));
	if (msh->temp_path != NULL)
		fprintf(stderr, "ret of unlink=%d\n", unlink(msh->temp_path));
*/
	return (0);
}

int	run_one_process(t_minishell *msh, t_cmd *cmd)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)cmd->args);
	fprintf(stderr, "one process, msh->args size=%zu\n", size);
	parse_redirection_part(msh, cmd, &cmd->args);
	if (ft_issymbol(&cmd->args[0]) != 0)
	{
		fprintf(stderr, "one process no command with redirection\n");
		ft_memdel_2dim(&cmd->args);
		cmd->args = NULL;
	}
	if (execute_one_command(msh, cmd, cmd->args) == 1)
		return (1);
	fprintf(stderr, "one ps exit 0\n");
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

int	run_one_command(t_minishell *msh, t_cmd *cmd)
{
	pid_t	pid;
	size_t	size;

	//args = split_command_string(cmd);
	size = ft_strlen_2dim((const char **)cmd->args);
	//printf("size=%zu\n", size);
	//print_2dim_string(msh->args, size);
	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return (1);
	}
	if (pid == 0)
	{
		if (run_one_process(msh, cmd) == 1)
		//if (execute_one_command(msh) == 1)
			return (1);
		return (0);
	}
	wait(NULL);
	return (0);
}
