#include "minishell.h"

static char	**malloc_temp_path(t_cmd *cmd)
{
	char	**temp_args;

	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return ((char **) NULL);
	temp_args[0] = ft_strdup(cmd->temp_path);
	temp_args[1] = NULL;
	return (temp_args);
}

static void	realloc_pipe_args_heredoc_paths(t_cmd *cmd, char ***pipe_args)
{
	*pipe_args = ft_strjoin_2dim_memdel(*pipe_args, malloc_temp_path(cmd));
	cmd->heredoc_paths = ft_strjoin_2dim_memdel(cmd->heredoc_paths,
			malloc_temp_path(cmd));
}

static int	parse_each_heredoc(t_minishell *msh, t_cmd *cmd, char ***pipe_args)
{
	char	**temp_args;
	size_t	size;
	size_t	j;

	size = ft_strlen_2dim((const char **)*pipe_args);
	j = -1;
	while (++j < size)
	{
		if (!ft_strcmp((*pipe_args)[j], "<<"))
		{
			if (execute_heredoc(msh, cmd, *pipe_args + j) == 1)
				return (1);
			*pipe_args = ft_strtrim_2dim_by_index(pipe_args, j, 2);
			if (check_command(pipe_args)
				&& !check_redirection_input((*pipe_args) + j))
				realloc_pipe_args_heredoc_paths(cmd, pipe_args);
			else
				unlink(cmd->temp_path);
			size -= 2;
			j--;
		}
	}
	return (0);
}

static char	**parse_heredocs(t_minishell *msh, t_cmd *cmd, char **args)
{
	char	**temp_args;
	char	**new_args;
	char	**pipe_args;
	size_t	i;

	i = -1;
	new_args = NULL;
	while (++i < cmd->pipe_count + 1)
	{
		pipe_args = parse_pipe_part(args, i);
		if (parse_each_heredoc(msh, cmd, &pipe_args) == 1)
			return ((char **) NULL);
		if (i != cmd->pipe_count)
		{
			temp_args = (char **)malloc(sizeof(char *) * 2);
			if (!temp_args)
				return ((char **) NULL);
			temp_args[0] = ft_strdup("|");
			temp_args[1] = NULL;
			pipe_args = ft_strjoin_2dim_memdel(pipe_args, temp_args);
		}
		new_args = ft_strjoin_2dim_memdel(new_args, pipe_args);
	}
	ft_memdel_2dim(&args);
	return (new_args);
}

char	**check_valid_redirection(t_minishell *msh, t_cmd *cmd, char **args)
{
	char	**new_args;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	if (check_syntax_error(msh, args, size) == 1)
		return ((char **) NULL);
	args = parse_heredocs(msh, cmd, args);
	return (args);
}
