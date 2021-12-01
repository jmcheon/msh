#include "minishell.h"

static size_t	get_pipe_count(char **args, int process_num, size_t *i)
{
	size_t	pipe_count;

	pipe_count = 0;
	if (process_num != 0)
	{
		while (args[*i] != NULL)
		{
			if (!ft_strcmp(args[(*i)++], "|"))
				pipe_count++;
			if (pipe_count == process_num)
				break ;
		}
	}
	return (pipe_count);
}

char	**parse_pipe_part(char **args, int process_num)
{
	char	**new_args;
	size_t	i;
	size_t	command_length;
	size_t	start_index;
	size_t	pipe_count;

	i = 0;
	pipe_count = get_pipe_count(args, process_num, &i);
	start_index = i;
	command_length = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i++], "|"))
			command_length++;
		if (args[i] == NULL || !ft_strcmp(args[i], "|"))
			break ;
	}
	new_args = (char **)malloc(sizeof(char *) * (command_length + 1));
	if (!new_args)
		return ((char **) NULL);
	i = 0;
	while (i < command_length)
		new_args[i++] = ft_strdup(args[start_index++]);
	new_args[i] = NULL;
	return (new_args);
}
