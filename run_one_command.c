#include "minishell.h"

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
		
	free_msh(msh, 1);
	//return (0);
	exit(0);
}

int	run_one_command(t_minishell *msh, t_cmd *cmd)
{
	pid_t	pid;
	size_t	size;
	int	wstatus;

	//args = split_command_string(cmd);
	size = ft_strlen_2dim((const char **)cmd->args);
	//printf("size=%zu\n", size);
	//print_2dim_string(msh->args, size);
	msh->g_pid = fork();
	if (msh->g_pid == -1)
	{
		perror("fork()");
		return (1);
	}
	if (msh->g_pid == 0)
	{
		if (run_one_process(msh, cmd) == 1)
		{
		//if (execute_one_command(msh) == 1)
			if (msh->ret != NULL)
			{
				printf("one cmd:%s\n", msh->ret);
				ft_memdel(&msh->ret);
				//free_msh(msh);
			}
			fprintf(stderr, "exit status in run one command=%d\n", msh->exit_status);
			free_msh(msh, 1);
			exit (msh->exit_status);
			//return (msh->exit_status);
		}
		fprintf(stderr, "exit status in no ret run one command=%d\n", msh->exit_status);
		return (0);
	}
	wait(&wstatus);
	if (WEXITSTATUS(wstatus))
	{
		fprintf(stderr, "run one command wstatus=%d\n", WEXITSTATUS(wstatus));
		return (WEXITSTATUS(wstatus));
	}
	return (0);
}
