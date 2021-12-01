#include "minishell.h"

static int	realloc_heredoc_paths(t_minishell *msh)
{
	char	**temp_args;
	size_t	i;

	i = 0;
	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return (1);
	temp_args[0] = ft_strdup(msh->cmd.temp_path);
	temp_args[1] = NULL;
	msh->cmd.heredoc_paths = ft_strjoin_2dim_memdel(msh->cmd.heredoc_paths, temp_args);
	return (0);
}

static int	parse_each_heredoc(t_minishell *msh, char ***pipe_args, int i)
{
	char	**temp_args;
	size_t	size;
	size_t	j;
	//size_t	is_command;

	size = ft_strlen_2dim((const char **)*pipe_args);
	j = 0;
	while (j < size)
	{
		if (!ft_strcmp((*pipe_args)[j], "<<"))
		{
			//is_command = check_command(pipe_args);
			//msh->cmd.flags.redirection_input = check_redirection_input
				//((*pipe_args) + j + 1);
			if (execute_heredoc(msh, *pipe_args + j) == 1)
				return (1);
			*pipe_args = ft_substr_2dim(pipe_args, j, 2);
			//printf("is_command, redir_input = (%zu, %d)\n", check_command(pipe_args), msh->cmd.flags.redirection_input);
		fprintf(stderr, "is_command, redir_input = (%zu, %zu)\n",check_command(pipe_args),check_redirection_input((*pipe_args) + j));
		//printf("*(*pipe_args) + j=%s\n", *((*pipe_args) + j + 1));
			if (check_command(pipe_args) && check_redirection_input((*pipe_args) + j) == 0)
			//if (check_command(pipe_args) && msh->cmd.flags.redirection_input == 0)
			{
				temp_args = (char **)malloc(sizeof(char *) * 2);
				if (!temp_args)
					return (1);
				temp_args[0] = ft_strdup(msh->cmd.temp_path);
				temp_args[1] = NULL;
				*pipe_args = ft_strjoin_2dim_memdel(*pipe_args, temp_args);
				realloc_heredoc_paths(msh);
			}
			else
				unlink(msh->cmd.temp_path);
			size -= 2;
			j--;
			//printf("check valid readline new_args\n");
			//print_2dim_string(new_args, size);
		}
		j++;
	}
	return (0);
}

static char	**parse_heredocs(t_minishell *msh, char **args)
{
	char	**temp_args;
	char	**new_args;
	char	**pipe_args;
	size_t	size;
	size_t	i;
	size_t	j;
	size_t	is_command;

	i = 0;
	new_args = NULL;
	is_command = 0;
	while (i < msh->cmd.pipe_count + 1)
	{
		pipe_args = parse_pipe_part_by_index(args, i);
		if (parse_each_heredoc(msh, &pipe_args, i) == 1)
			return ((char **) NULL);
/*
		size = ft_strlen_2dim((const char **)pipe_args);
		j = 0;
		while (j < size)
		{
			if (!ft_strcmp(pipe_args[j], "<<"))
			{
				if (check_command(&pipe_args) == 1)
					is_command = 1;
				if (check_redirection_input(pipe_args + j + 1) == 1)
					msh->cmd.flags.redirection_input = 1;
				else
					msh->cmd.flags.redirection_input = 0;
				if (get_next_heredoc_command(msh, pipe_args + j, i) == 1)
					return ((char **) NULL);
				pipe_args = ft_substr_2dim(&pipe_args, j, 2);
				//printf("is_command, redir_input = (%zu, %d)\n", is_command, msh->flags.redirection_input);
				if (is_command == 1 && msh->cmd.flags.redirection_input == 0)
				{
					temp_args = (char **)malloc(sizeof(char *) * 2);
					if (!temp_args)
						return ((char **) NULL);
					temp_args[0] = ft_strdup(msh->cmd.temp_path);
					temp_args[1] = NULL;
					pipe_args = ft_strjoin_2dim_memdel(pipe_args, temp_args);
					realloc_heredoc_paths(msh);
				}
				else
					unlink(msh->cmd.temp_path);
				size -= 2;
				j--;
				//printf("check valid readline new_args\n");
				//print_2dim_string(new_args, size);
			}
			j++;
		}
*/
		if (i != msh->cmd.pipe_count)
		{
			temp_args = (char **)malloc(sizeof(char *) * 2);
			if (!temp_args)
				return ((char **) NULL);
			temp_args[0] = ft_strdup("|");
			temp_args[1] = NULL;
			pipe_args = ft_strjoin_2dim_memdel(pipe_args, temp_args);
			//	new_args = ft_strjoin_2dim((const char **)new_args, "|");
		}
		new_args = ft_strjoin_2dim_memdel(new_args, pipe_args);
		//ft_memdel_2dim(*pipe_args);
		i++;
	}
	ft_memdel_2dim(&args);
	return (new_args);
}

char	**check_valid_redirection(t_minishell *msh, char **args)
{
	char	**new_args;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	//printf("bf < syntax check readline args\n");
	//print_2dim_string(args, size);
	if (check_syntax_error(msh, args, size) == 1)
		return ((char **) NULL);
	args = parse_heredocs(msh, args);
	//printf("check valid readline args\n");
	//print_2dim_string(args, size);
	return (args);
}
