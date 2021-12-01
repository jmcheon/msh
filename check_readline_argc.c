#include "minishell.h"

size_t	check_single_quote(char *line, size_t i)
{
	while (line[i] != Q_SINGLE && line[i] != '\0')
		i++;
	i++;
	if (line[i] != '\0' && line[i] != ' '
		&& line[i] != Q_DOUBLE && line[i] != Q_SINGLE)
	{
		if (line[i] >= 33 && line[i] <= 126)
		{
			while (line[i + 1] != '\0')
			{
				if ((line[i] != '\\'
						&& (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
					|| (!((line[i + 1] != Q_SINGLE || line[i + 1] != Q_DOUBLE)
							&& line[i + 1] != ' ')))
					break ;
				i++;
			}
		}
		i++;
	}
	if (line[i] == Q_DOUBLE)
		i += check_double_quote((line + i + 1), 0) + 1;
	if (line[i] != '\0' && line[i] == Q_SINGLE)
		i += check_single_quote((line + i + 1), 0) + 1;
	return (i);
}

size_t	check_double_quote(char *line, size_t i)
{
	while (line[i] != Q_DOUBLE && line[i] != '\0')
		i++;
	i++;
	if (line[i] != '\0' && line[i] != ' '
		&& line[i] != Q_DOUBLE && line[i] != Q_SINGLE)
	{
		if (line[i] != Q_DOUBLE && line[i] >= 33 && line[i] <= 126)
		{
			while (line[i + 1] != '\0')
			{
				if ((line[i] != '\\'
						&& (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
					|| (!((line[i + 1] != Q_SINGLE || line[i + 1] != Q_DOUBLE)
							&& line[i + 1] != ' ')))
					break ;
				i++;
			}
		}
		i++;
	}
	if (line[i] == Q_SINGLE)
		i += check_single_quote((line + i + 1), 0) + 1;
	if (line[i] != '\0' && line[i] == Q_DOUBLE)
		i += check_double_quote((line + i + 1), 0) + 1;
	return (i);
}

size_t	check_readline_argc(char *line)
{
	size_t	argc;
	size_t	i;
	size_t	size;

	size = ft_strlen(line);
	i = 0;
	argc = 0;
	while (i < size)
	{
		while (line[i] == ' ')
			i++;
		if (i == 0 && line[i] == Q_SINGLE)
		{
			argc++;
			i += check_single_quote((line + i + 1), 0);
			//fprintf(stderr, "line[%zu]=%c\n", i - 1, line[i - 1]);
			//fprintf(stderr, "line[%zu]=%c\n", i, line[i]);
		}
		else if (i == 0 && line[i] == Q_DOUBLE)
		{
			argc++;
			i += check_double_quote((line + i + 1), 0);
		}
		else if (i > 0 && (line[i - 1] != '\\' && line[i] == Q_SINGLE))
		{
			argc++;
			i += check_single_quote((line + i + 1), 0);
			//fprintf(stderr, "\\ string line[%zu]=%c\n", i, line[i]);
			//split_quotes(&args, line, &i);
		}
		else if (i > 0 && line[i - 1] != '\\' && (line[i] == Q_DOUBLE))
		{
			argc++;
			i += check_double_quote((line + i + 1), 0);
		}
		else if (line[i] >= 33 && line[i] <= 126)
		{
			fprintf(stderr, "check_readline_argc start noquote line[%zu]=%c\n", i, line[i]);
			argc++;
			//while (line[i + 1] != ' ' && line[i + 1] != '\0')
			//while (line[i + 1] != '\0'
			//		&& (line[i + 1] != Q_SINGLE && line[i + 1] != Q_DOUBLE) && line[i + 1] != ' ')
			//	i++;
			while (line[i + 1] != '\0')
			{
				if (line[i] != '\\' && (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
					break ;
				if (!((line[i + 1] != Q_SINGLE || line[i + 1] != Q_DOUBLE) && line[i + 1] != ' '))
					break ;
				i++;
			}
			//fprintf(stderr, "af string line + %zu=%s\n", i, line + i);
			i++;
			if (line[i] == Q_SINGLE)
				i += check_single_quote((line + i + 1), 0);
			else if (line[i] == Q_DOUBLE)
				i += check_double_quote((line + i + 1), 0);
		}
		//msh->cmd.args = ft_strjoin_2dim_memdel(msh->cmd.args, malloc_args(msh, ));
		i++;
	}
	return (argc);
}
