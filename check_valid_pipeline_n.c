#include "minishell.h"

static	int	get_next_pipe(t_minishell *msh, char ***new_args, size_t *size)
{
	char	*temp;
	char	*next_line;
	char	**temp_args;
	int		argc;
	int		ret;

	next_line = NULL;
	argc = 0;
	while (argc == 0)
	{
		if (next_line != NULL)
			ft_memdel(&next_line);
		write(STDOUT_FILENO, "> ", 2);
		ret = get_next_line(&next_line);
		temp = next_line;
		next_line = ft_strjoin(" ", temp);
		free(temp);
		argc = check_readline_argc(next_line);
		if (argc == 0 && ret < 1)
		{
			if (execute_syntax_error(msh, NULL, -2))
			{
				ft_memdel(&next_line);
				ft_memdel_2dim(new_args);
				return (1);
			}
		}
	}
	temp_args = split_readline(next_line);
	ft_memdel(&next_line);
	*new_args = ft_strjoin_2dim_memdel(*new_args, temp_args);
	*size = ft_strlen_2dim((const char **)*new_args);
	return (0);
}

char	**check_valid_pipeline(t_minishell *msh, char **args, size_t size)
{
	char	**new_args;
	size_t	i;

	i = 0;
	if (check_syntax_error(msh, args, size) == 1)
		return ((char **) NULL);
	if (!ft_strcmp(args[size - 1], "|"))
	{
		new_args = ft_strdup_2dim((const char **)args);
		ft_memdel_2dim(&args);
		if (get_next_pipe(msh, &new_args, &size) == 1)
			return ((char **) NULL);
		if (check_syntax_error(msh, new_args, size) == 1)
			return ((char **) NULL);
		while (!ft_strcmp(new_args[size - 1], "|"))
		{
			if (get_next_pipe(msh, &new_args, &size) == 1)
				return ((char **) NULL);
		}
		if (check_syntax_error(msh, new_args, size) == 1)
			return ((char **) NULL);
		return (new_args);
	}
	return (args);
}
