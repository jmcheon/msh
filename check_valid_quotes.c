#include "minishell.h"
void	check_quote_characters(t_flags *flags, char *line)
{
	size_t	i;

	i = 0;
		fprintf(stderr, "line=%s, strlen=%zu\n", line, ft_strlen(line));
	while (i < ft_strlen(line))// && line[i] != '\0')
	{
		if (flags->q_double == 1 && line[i] == Q_DOUBLE)
		{
			flags->q_double = 0;
			i++;
		}
		else if (flags->q_single == 1 && line[i] == Q_SINGLE)
		{
			flags->q_single = 0;
			i++;
		}
		if (flags->q_single == 0 && (i > 0 &&  line[i - 1] != '\\') && line[i] == Q_DOUBLE)
			flags->q_double = 1;
		else if (flags->q_double == 0 && (i > 0 && line[i - 1] != '\\') && line[i] == Q_SINGLE)
			flags->q_single = 1;
		if (flags->q_single == 0 && (i == 0 && line[i] == Q_DOUBLE))
			flags->q_double = 1;
		else if (flags->q_double == 0 && (i == 0 && line[i] == Q_SINGLE))
			flags->q_single = 1;
		i++;
	}
}

void	check_quote_characters_old(t_flags *flags, char *line)
{
	size_t	i;

	while (i < ft_strlen(line) && ft_strlen(line) <= 1)
	{
		if (flags->q_double == 1 && line[i] == Q_DOUBLE)
		{
			fprintf(stderr, "3. line[%zu] = %c, single, double = (%d, %d)\n", i, line[i], flags->q_single, flags->q_double);
			flags->q_double = 0;
			i++;
		}
		else if (flags->q_single == 1 && line[i] == Q_SINGLE)
		{
			fprintf(stderr, "4. line[%zu] = %c, single, double = (%d, %d)\n", i, line[i], flags->q_single, flags->q_double);
			flags->q_single = 0;
			i++;
		}
		if (flags->q_single == 0 && line[i] == Q_DOUBLE)
			flags->q_double = 1;
		else if (flags->q_double == 0 && line[i] == Q_SINGLE)
			flags->q_single = 1;
		i++;
	}
	i = 0;
	while (i < ft_strlen(line))// && line[i] != '\0')
	{
		if (flags->q_double == 1 && line[i] == Q_DOUBLE)
		{
			flags->q_double = 0;
			fprintf(stderr, "3. line[%zu] = %c, single, double = (%d, %d)\n", i, line[i], flags->q_single, flags->q_double);
			i++;
		}
		else if (flags->q_single == 1 && line[i] == Q_SINGLE)
		{
			flags->q_single = 0;
			fprintf(stderr, "4. line[%zu] = %c, single, double = (%d, %d)\n", i, line[i], flags->q_single, flags->q_double);
			i++;
		}
		if (flags->q_single == 0 && line[i] == Q_DOUBLE)
		{
			flags->q_double = 1;
			fprintf(stderr, "1. line[%zu] = %c, single, double = (%d, %d)\n", i, line[i], flags->q_single, flags->q_double);
		}
		else if (flags->q_double == 0 && line[i] == Q_SINGLE)
		{
			flags->q_single = 1;
			fprintf(stderr, "2. line[%zu] = %c, single, double = (%d, %d)\n", i, line[i], flags->q_single, flags->q_double);
		}
		i++;
	}
}

static int	get_next_quotes(t_minishell *msh, t_flags *flags, char **line, int c)
{
	char	*temp;
	char	*next_line;
	int	argc;
	int	ret;

	next_line = NULL;
	argc = 0;
	//msh->cmd[0].line = ft_strjoin_memdel(msh->cmd[0].line, ft_strdup("\n"));
	*line = ft_strjoin_memdel(*line, ft_strdup("\n"));
	fprintf(stderr, "ft_strchr(next_line, Q_SINGLE)=%s\n", ft_strchr(next_line, Q_SINGLE));
	//fprintf(stderr, "ft_strchr(msh->cmd[0].line, Q_SINGLE)=%s\n", ft_strchr(msh->cmd[0].line, Q_SINGLE));
	fprintf(stderr, "ft_strchr(line, Q_SINGLE)=%s\n", ft_strchr(*line, Q_SINGLE));
	while ((flags->q_single == 1 && c == Q_SINGLE) 
		|| (flags->q_double == 1 && c == Q_DOUBLE))
	{
		fprintf(stderr, "while ft_strchr(next_line, Q_SINGLE)=%s\n", ft_strchr(next_line, Q_SINGLE));
		if (next_line != NULL)
			ft_memdel(&next_line);
		write(STDOUT_FILENO, ">\"", 2);
		ret = get_next_line(&next_line);
		check_quote_characters(flags, next_line);
		if ((flags->q_single == 1 && c == Q_SINGLE) 
				|| (flags->q_double == 1 && c == Q_DOUBLE))
			//msh->cmd[0].line = ft_strjoin_memdel(msh->cmd[0].line, ft_strjoin(next_line, "\n"));
			*line = ft_strjoin_memdel(*line, ft_strjoin(next_line, "\n"));
		else
			//msh->cmd[0].line = ft_strjoin_memdel(msh->cmd[0].line, next_line);
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

int	check_quotes(t_minishell *msh, char **line)
{
	t_flags	flags;
	int	err;

	err = 0;
	init_flags(&flags);
	check_quote_characters(&flags, *line);
	if (flags.q_single == 1)
		err = get_next_quotes(msh, &flags, line, Q_SINGLE);
	else if (flags.q_double == 1)
		err = get_next_quotes(msh, &flags, line, Q_DOUBLE);
	return (err);
}
