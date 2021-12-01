#include "minishell.h"

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

char	*check_redirection(t_minishell *msh, char **line)
{
	char	*new_line;
	size_t	i;
	size_t	argc;

	i = 0;
	new_line = NULL;
	argc = check_readline_argc(*line);
	fprintf(stderr, "check argc=%zu$\n", argc);
	if (argc > 0)
	{
		fprintf(stderr, "plus size=%zu, line=%s$\n", get_new_line_size(*line), *line);
		new_line =  rmalloc_line(*line, get_new_line_size(*line));
		//size = ft_strlen(new_line);
		argc = check_readline_argc(new_line);
		fprintf(stderr, "rmalloc line=%s, argc=%zu\n", new_line, argc);
	}
/*
	if (check_readline_syntax_error(msh, *line) == 1)
		return (1);
	argc = check_readline_argc(*line);
	if (argc > 0)
	{
		if ((*line)[i - 1] != '\\' && (*line)[i] == '<' && (*line)[i + 1] == '<')
		{
			if (get_next_pipe(msh, line) == 1)
				return (1);
		}
	}
*/
	return (NULL);
}
