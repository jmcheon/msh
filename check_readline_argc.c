#include "minishell.h"

size_t	check_single_quote(char *line, size_t *argc)
{
	size_t	i;

	i = 0;
	fprintf(stderr, " q single line=%s\n", line);
	//if (line[i] == Q_SINGLE)
		//return (1);
	while (line[i] != Q_SINGLE && line[i] != '\0') 
		i++;
	fprintf(stderr, " q single last quote line[%zu]=%c\n", i, line[i]);
	i++;
	if (line[i] != '\0' && line[i] != Q_DOUBLE && line[i] != Q_SINGLE)
	{
		if (line[i] != Q_SINGLE && line[i] >= 33 && line[i] <= 126)
		{
			while (line[i + 1] != Q_SINGLE && line[i + 1] != Q_DOUBLE && line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
		}
		i++;
	}
	if (line[i] == Q_DOUBLE)
	{
		i += check_double_quote((line + i + 1), argc);
		i++;
	}
	fprintf(stderr, " q single line[%zu]=%c\n", i, line[i]);
	if (line[i] != '\0' && line[i] == Q_SINGLE)
	{
		i += check_single_quote((line + i + 1), argc);
		i++;
	}
	//(*argc)++;
	return (i);
}

size_t	check_double_quote(char *line, size_t *argc)
{
	size_t	i;

	i = 0;
	fprintf(stderr, " q double line=%s\n", line);
	if (line[i] == Q_DOUBLE)
		return (1);
	while (line[i] != Q_DOUBLE && line[i] != '\0') 
		i++;
	i++;
	//if (line[i] != '\0' && line[i] != Q_SINGLE)
	if (line[i] != '\0' && line[i] != Q_DOUBLE && line[i] != Q_SINGLE)
	{
		if (line[i] != Q_DOUBLE && line[i] >= 33 && line[i] <= 126)
		{
			//while (line[i + 1] != Q_DOUBLE && line[i + 1] != ' ' && line[i + 1] != '\0')
			while (line[i + 1] != Q_SINGLE && line[i + 1] != Q_DOUBLE && line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
		}
		i++;
	}
	if (line[i] == Q_SINGLE)
	{
		i += check_single_quote((line + i + 1), argc);
		i++;
	}
	fprintf(stderr, " q double line[%zu]=%c\n", i, line[i]);
	if (line[i] != '\0' && line[i] == Q_DOUBLE)
	{
		i += check_double_quote((line + i + 1), argc);
		i++;
	}
	//(*argc)++;
	return (i);
}

static char	**malloc_args(char *str)
{
	char	**temp_args;

	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return ((char **) NULL);
	temp_args[0] = ft_strdup(str);
	temp_args[1] = NULL;
	return (temp_args);
}

static char	*ft_strdup_by_index(char *line, size_t start, size_t end)
{
	char	*dst;
	size_t	i;

	fprintf(stderr, "line[%zu]=%c\n", start, line[start]);
	fprintf(stderr, "line[%zu]=%c\n", end, line[end]);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!dst)
		return (NULL);
	while (start <= end)
		dst[i++] = line[start++];
	dst[i] = '\0';
	return (dst);
}

static size_t	check_next_single_quote(char *line)
{
	size_t	i;

	i = 0;
	fprintf(stderr, " split char q single line=%s\n", line);
	while (line[i] != Q_SINGLE && line[i] != '\0') 
		i++;
	i++;
	return (i);
}

char	*rmalloc_line(char *line, size_t size)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(line) + size + 1));
	if (!dst)
		return (NULL);
	while (i < ft_strlen(line))
	{
		
		if (line[i] == Q_SINGLE)
		{
			dst[j++] = line[i++];
			while (line[i] != Q_SINGLE && line[i] != '\0') 
				dst[j++] = line[i++];
			//printf("single line[%zu]=%c\n", i, line[i]);
			dst[j++] = line[i++];
		}
		else if (line[i] == Q_DOUBLE)
		{
			dst[j++] = line[i++];
			while (line[i] != Q_DOUBLE && line[i] != '\0') 
				dst[j++] = line[i++];
			//printf("double line[%zu]=%c\n", i, line[i]);
			dst[j++] = line[i++];
		}
		else if (i == 0 && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
		{
			printf("0\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else if (i == 0 && (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<'))
		{
			printf("1\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else if ((i > 0 && line[i - 1] != '\\') && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
		//else if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
		{
			printf("2\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else if ((i > 0 && line[i - 1] != '\\') && (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<'))
		//else if (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<')
		{
			printf("3\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else 
		{
			printf("4\n");
			if ((i > 0 && line[i - 1] == '\\') && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
			{
				dst[j++] = line[i++];
				dst[j++] = line[i++];
			}
			//printf("line[%zu]=%c\n", i, line[i]);
			else if (line[i] != '\0')
				dst[j++] = line[i++];
		}
/*
		if (line[i] != '|' && (line[i] >= 33 && line[i] <= 126))
		dst[j++] = ' ';
		while (line[i] != '\0' && line[i] != ' ' && line[i] != Q_SINGLE && line[i] != Q_DOUBLE 
				&& line[i] != '|' && line[i] != ';' && line[i] != '>' && line[i] != '<'
				&& ((line[i] != '<' && line[i + 1] != '<') || (line[i] != '>' && line[i + 1] != '>')))
			dst[j++] = line[i++];
		i++;
*/
	}
	dst[j] = '\0';
	return (dst);
}

size_t	get_new_line_size(char *line)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == Q_SINGLE)
		{
			while (line[i + 1] != Q_SINGLE && line[i + 1] != '\0') 
				i++;
			i++;
		}
		if (line[i] == Q_DOUBLE)
		{
			while (line[i + 1] != Q_DOUBLE && line[i + 1] != '\0') 
				i++;
			i++;
		}
		if ((i > 0 && line[i - 1] != '\\') && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
		//if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
		{
			size += 2;
			i += 2;
		}
		if ((i > 0 && line[i - 1] != '\\') && (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<'))
		//if (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<')
		{
			size += 2;
		}
		if (i == 0 && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
		{
			size += 2;
			i += 2;
		}
		if (i == 0 && (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<'))
		{
			size += 2;
		}
		i++;
	}
	return (size);
}

char	**split_readline_by_argc(t_minishell *msh, char *line)
{
	char	**args;
	char	**temp_args;
	char	*temp;
	char	*temp2;
	char	*new_line;
	size_t	argc;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	args = NULL;
	new_line = NULL;
	argc = 0;
	argc = check_readline_argc(line);
	fprintf(stderr, "check argc=%zu$\n", argc);
	if (argc > 0)
	{
		fprintf(stderr, "plus size=%zu, line=%s$\n", get_new_line_size(line), line);
		new_line =  rmalloc_line(line, get_new_line_size(line));
		fprintf(stderr, "rmalloc line=%s\n", new_line);
		size = ft_strlen(new_line);
		argc = check_readline_argc(new_line);
	}
	while (argc > 0 && i < size)
	{
		while (new_line[i] == ' ')
			i++;
		if (new_line[i] == Q_SINGLE)
		{
			//i += check_single_quote((new_line + i + 1), &argc);
			j = i;
			i += check_single_quote((new_line + i + 1), &argc);
			if (j + 1 == i)
			{
				temp = ft_strdup_by_index(new_line, j, i);
				fprintf(stderr, "no char temp=%s\n", temp);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp));
				ft_memdel(&temp);
			}
			else
			{
				temp = ft_strdup_by_index(new_line, j, i);
				//next_quote_i = check_next_single_quote(temp + 1);
				fprintf(stderr, "temp=%s\n", temp);
				//fprintf(stderr, "new_line + %zu=%s, next single quote=%zu\n", j, new_line + j, check_next_single_quote(new_line + j + 1));
				//fprintf(stderr, "temp + 1=%s\n", temp + next_quote_i);
				fprintf(stderr, "split readline by argc new line=%s, (j,i)=(%zu,%zu)\n", temp, j, i);
				temp2 = omit_quotes(temp);
				fprintf(stderr, "temp2=%s\n", temp2);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp2));
				ft_memdel(&temp);
				ft_memdel(&temp2);
			}
			//fprintf(stderr, "new_line[%zu]=%c\n", i - 1, new_line[i - 1]);
			//fprintf(stderr, "new_line[%zu]=%c\n", i, new_line[i]);
		}
		else if (new_line[i] == Q_DOUBLE)
		{
			j = i;
			i += check_double_quote((new_line + i + 1), &argc);
			if (j + 1 == i)
			{
				temp = ft_strdup_by_index(new_line, j, i);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp));
				ft_memdel(&temp);
			}
			else
			{
				temp = ft_strdup_by_index(new_line, j, i);
				//next_quote_i = check_double_quote(temp + 1, &argc);
				//temp2 = omit_character(temp, next_quote_i, Q_DOUBLE);
				//temp2 = omit_character(temp, Q_DOUBLE);
				temp2 = omit_quotes(temp);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp2));
				ft_memdel(&temp);
				ft_memdel(&temp2);
			}
		}
		else if (new_line[i] >= 33 && new_line[i] <= 126)
		{
			j = i;
			//while (new_line[i + 1] != Q_SINGLE && new_line[i + 1] != Q_DOUBLE && new_line[i + 1] != ' ' && new_line[i + 1] != '\0')
			while (new_line[i + 1] != ' ' && new_line[i + 1] != '\0')
				i++;
			temp = ft_strdup_by_index(new_line, j, i);
			temp2 = omit_quotes(temp);
			ft_memdel(&temp);
			//temp = omit_character(temp2, '\\');
			temp_args = split_character(malloc_args(temp2), '|');
			temp_args = split_character(temp_args, ';');
			temp_args = split_string(temp_args, "<<");
			temp_args = split_string(temp_args, ">>");
			temp_args = split_character(temp_args, '<');
			temp_args = split_character(temp_args, '>');
			args = ft_strjoin_2dim_memdel(args, temp_args);
			//args = ft_strjoin_2dim_memdel(args, malloc_args(temp));
			//size = ft_strlen_2dim((const char **)args);
			//fprintf(stderr, "split readnew_line argc no quotes, %zu, %zu\n", i, size);
			//fprintf(stderr, "args[0]=%s\n", args[0]);
			//fprintf(stderr, "args[1]=%s\n", args[1]);
			print_2dim_string(args, ft_strlen_2dim((const char **)args));
			ft_memdel(&temp);
			ft_memdel(&temp2);
		}
		//msh->cmd.args = ft_strjoin_2dim_memdel(msh->cmd.args, malloc_args(msh, ));
		i++;
	}
	ft_memdel(&new_line);
	return (args);
}
