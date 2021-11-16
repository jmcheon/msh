#include "minishell.h"

void	init_flags(t_flags *flags)
{
	//flags->valid_fd = 0;
	//flags->redirection_input = 0;
	flags->q_single = 0;
	flags->q_double = 0;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->args = NULL;
	cmd->temp_path = NULL;
	cmd->heredoc_paths = NULL;
	cmd->pipe_count = 0;
	cmd->valid_fd = 0;
	//init_flags(&cmd->flags);
}

void	init_msh(t_minishell *msh, char **envp)
{
	msh->ret = NULL;
	msh->envp = envp;
	msh->stdfd[0] = dup(STDIN_FILENO);
	msh->stdfd[1] = dup(STDOUT_FILENO);
	msh->cmd_count = 1;
	msh->cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	init_cmd(&msh->cmd[0]);
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->line != NULL)
		ft_memdel(&cmd->line);
	if (cmd->args != NULL)
		ft_memdel_2dim(&(cmd->args));
	if (cmd->heredoc_paths != NULL)
	{
		while (i < ft_strlen_2dim((const char **)cmd->heredoc_paths))
			unlink(cmd->heredoc_paths[i++]);
		ft_memdel_2dim(&(cmd->heredoc_paths));
		fprintf(stderr, "free cmd heredoc path freed\n");
	}
	if (cmd->temp_path != NULL)
	{
		unlink(cmd->temp_path);
		ft_memdel(&(cmd->temp_path));
	}
	//free(cmd);
	//init_cmd(cmd);
	//init_flags(&cmd->flags);
}

void	free_msh(t_minishell *msh)
{
	size_t	i;

	i = 0;
//	while (i < msh->cmd_count)
//		free_cmd(&msh->cmd[i++]);
	free(msh->cmd);
	if (msh->ret != NULL)
		ft_memdel(&(msh->ret));
	close(msh->stdfd[0]);
	close(msh->stdfd[1]);
}
