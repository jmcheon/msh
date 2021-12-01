#include "minishell.h"

/*
function		: to split readline by lexical unit
first parameter		: 1 dimensional string
return value		: splited 2 dimensional string
*/

char	**split_readline(char *line)
{
	char	**args;
	size_t	i;
	size_t	j;
	int	argc;

	argc = check_readline_argc(line);
	fprintf(stderr, "argc=%d\n", argc);
	if (argc > 1)
		args = ft_split(line, ' ');
	else if (argc == 1)
	{
		args = (char **)malloc(sizeof(char *) * 2);
		if (!args)
			return ((char **)NULL);
		//printf("line=%s$\n", line);
		args[0] = ft_strdup(line);
		i = 0;
		j = 0;
		while (line[i] != '\0')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] != '\0' && line[i] != ' ')
			{
				//printf("line[%zu]=%c\n", i, line[i]);
				args[0][j++] = line[i++];
			}
		}
		args[0][j] = '\0';
		//printf("args[0]=%s$\n", args[0]);
		args[1] = NULL; 
	}
	else if (argc == 0)
		return ((char **)NULL);
	args = split_character(args, '|');
	args = split_string(args, "<<");
	args = split_string(args, ">>");
	args = split_character(args, '<');
	args = split_character(args, '>');
	//print_2dim_string(args, ft_strlen_2dim((const char **)args));
	return (args);
}
