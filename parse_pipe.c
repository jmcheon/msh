#include "minishell.h"

/*
function		: to parse the part separated by pipes commands by ordinal number of process
first parameter		: 2 dimensional string
second parameter	: number of process (ordinal)
return value		: parsed 2 dimensional string
*/

char	**parse_pipe_part(char **args, int process_num)
{
	char	**new_args;
	size_t	i;
	size_t	command_length;
	size_t	start_index;
	size_t	pipe_count;

	i = 0;
	pipe_count= 0;
	if (process_num != 0)
	{
		while (args[i] != NULL)
		{
			//if (ft_strchr(args[i++], '|') != NULL)
			if (!ft_strcmp(args[i++], "|"))
				pipe_count++;
			if (pipe_count == process_num)
				break ;
		}
	}
	//printf("pipe_count=%zu, i=%zu, args[i]=%s\n", pipe_count, i, args[i]);
	//if (!ft_strcmp(args[i], "|"))
	//	return ((char **)NULL);
	start_index = i;
	command_length = 0;
	while (args[i] != NULL)
	{
		//if (ft_strcmp(args[i++], "|"))
		//if (ft_strchr(args[i++], '|') == NULL)
		if (ft_strcmp(args[i++], "|"))
			command_length++;
		if (args[i] == NULL || !ft_strcmp(args[i], "|"))
			break ;
	}
	//printf("cmd len=%zu, start=%zu, i=%zu\n", command_length, start_index, i);
	new_args = (char **)malloc(sizeof(char *) * (command_length + 1));
	if (!new_args)
		return ((char **)NULL);
	i = 0;
	while (i < command_length)
		new_args[i++] = ft_strdup(args[start_index++]);
	new_args[i] = NULL;
	fprintf(stderr, "$-----parse_pipe_part, ps num %d---$\n", process_num);
	print_2dim_string(new_args, command_length);
	return (new_args);
}
