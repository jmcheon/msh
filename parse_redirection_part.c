#include "minishell.h"

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
			*pipe_args = ft_substr_2dim(pipe_args, i, 2);
			size -= 2;
			i--;
		}
		else if ((!ft_strcmp((*pipe_args)[i], ">"))
			|| (!ft_strcmp((*pipe_args)[i], ">>")))
		{
			if (redirect_output(msh, (*pipe_args)[i], (*pipe_args)[i + 1]) == 1)
				cmd->valid_fd = -1;
			*pipe_args = ft_substr_2dim(pipe_args, i, 2);
			size -= 2;
			i--;
		}
		i++;
	}
	//size = ft_strlen_2dim((const char **)msh->args);
	//fprintf(stderr, "$-----parse_redirection_part------$\n");
	//print_2dim_string(*pipe_args, ft_strlen_2dim((const char **)*pipe_args));
}
