#include "minishell.h"

static size_t check_last_character(char *line)
{
	size_t	i;
	size_t	last;

	i = 0;
	//printf("line=%s$, last ch=%c$\n", line, line[ft_strlen(line) - 1]);
	//last = 0;
	while (i < ft_strlen(line))// && line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		if ((line[i] >= 33 && line[i] <= 126))
		{
			while (line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
			last = i;
		}
		i++;
	}
	//printf("last=%d$, line[last]=%c\n", last, line[last]);
	return (last);
}

static size_t check_pipe_character(char *line)
{
	size_t	i;
	size_t	last;

	i = 0;
	//printf("line=%s$, last ch=%c$\n", line, line[ft_strlen(line) - 1]);
	//last = 0;
	while (i < ft_strlen(line))// && line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		if ((line[i] >= 33 && line[i] <= 126))
		{
			while (line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
			last = i;
		}
		i++;
	}
	//printf("last=%d$, line[last]=%c\n", last, line[last]);
	if (line[last] == '|')
		return (1);
	else
		return (0);
}

static	int	get_next_pipe(t_minishell *msh, char **line)
{
	char	*next_line;
	int	is_pipe;
	int	argc;
	int	ret;

	next_line = NULL;
	argc = 0;
	*line = ft_strjoin_memdel(*line, ft_strdup(" "));
	is_pipe = 1;
	while (is_pipe)
	{
		if (next_line != NULL)
			ft_memdel(&next_line);
		write(STDOUT_FILENO, ">|", 2);
		ret = get_next_line(&next_line);
		fprintf(stderr, "\t\tnext_line=%s\n", next_line);
		if (check_readline_syntax_error(msh, next_line) == 1)
		{
			*line = ft_strjoin_memdel(*line, next_line);
			return (1);
		}
		if (check_quotes(msh, &next_line) == 1)
		{
			*line = ft_strjoin_memdel(*line, next_line);
			return (1);
		}
		is_pipe = check_pipe_character(next_line);
		if (is_pipe)
			*line = ft_strjoin_memdel(*line, ft_strjoin(next_line, " "));
		else
			*line = ft_strjoin_memdel(*line, next_line);
/*
		argc = check_readline_argc(next_line);
		if (argc == 0 && ret < 1)
		{
			printf("ctrl + d\n");
			temp = ft_itos(c);
			if (execute_syntax_error(msh, temp, -5))
			{
				printf("???\n");
				ft_memdel(&temp);
				ft_memdel(&next_line);
				return (1);
			}
		}
*/
		//printf("argc=%d, ret=%d\n", argc, ret);
	}
	//ft_memdel(&next_line);
	return (0);
}

int	check_pipeline(t_minishell *msh, char **line)
{
	size_t	i;
	size_t	argc;

	i = 0;
	if (check_readline_syntax_error(msh, *line) == 1)
		return (1);
	argc = check_readline_argc(*line);
	if (argc > 0)
	{
		if ((*line)[check_last_character(*line) - 1] != '\\' && (*line)[check_last_character(*line)] == '|')
		{
			if (get_next_pipe(msh, line) == 1)
				return (1);
		}
	}
	return (0);
}
