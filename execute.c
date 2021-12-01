#include "minishell.h"

int	execute_one_command(t_minishell *msh, t_cmd *cmd, char **args)
{
	char	*temp;

	temp = NULL;
	if (cmd->valid_fd < 0)
		cmd->valid_fd = 0;
	else if (args != NULL && (args[0][0] == '/'
		|| (args[0][0] == '.' && args[0][1] == '/')
		|| (args[0][0] == '.' && args[0][1] == '.' && args[0][2] == '/')))
	{
		if (execve(args[0], args, msh->envp) == -1)
		{
			ft_memdel(&msh->ret);
			temp = ft_strjoin(args[0], ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
			msh->exit_status = 127;
		}
	}
	else if (args != NULL)
	{
	//	fprintf(stderr, "one args is not null ft_execve\n");
		if (ft_execve(msh, args) == 1)
			return (1);
		if (msh->exit_status != 0 && msh->ret == NULL)
		{
			return (1);
		}
	}
	else
	{
		//fprintf(stderr, "execute one no command\n");
		dup2(msh->stdfd[0], STDIN_FILENO);
		dup2(msh->stdfd[1], STDOUT_FILENO);
		//return (1);
	}
	if (msh->ret != NULL)
	{
		//fprintf(stderr, "error one cmd\n");
		dup2(msh->stdfd[0], STDIN_FILENO);
		dup2(msh->stdfd[1], STDOUT_FILENO);
		return (1);
	}
	return (0);
}
