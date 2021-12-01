#include "minishell.h"

char	*rmalloc_line(char *line, size_t size)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size <= 0)
		return (ft_strdup(line));
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
			//printf("0\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else if (i == 0 && (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<'))
		{
			//printf("1\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else if ((i > 0 && line[i - 1] != '\\') && ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>')))
		//else if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
		{
			//printf("2\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else if ((i > 0 && line[i - 1] != '\\') && (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<'))
		//else if (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<')
		{
			//printf("3\n");
			dst[j++] = ' ';
			dst[j++] = line[i++];
			dst[j++] = ' ';
		}
		else 
		{
			//printf("4\n");
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

static void	split_quotes(char ***args, char *new_line, size_t *i)
{
	char	*temp;
	char	*temp2;
	size_t	j;

	temp = NULL;
	temp2 = NULL;
	if (new_line[*i] == Q_SINGLE)
	{
		j = *i;
		(*i) += check_single_quote((new_line + (*i) + 1), 0);
		temp = ft_strdup_by_index(new_line, j, *i);
		//temp2 = omit_quotes(temp);
		//temp2 = omit_double_quote(temp);
		//temp2 = omit_single_quote(temp);
		*args = ft_strjoin_2dim_memdel(*args, malloc_args(temp));
		ft_memdel(&temp);
		ft_memdel(&temp2);
	}
	else if (new_line[*i] == Q_DOUBLE)
	{
		j = *i;
		(*i) += check_double_quote((new_line + (*i) + 1), 0);
		temp = ft_strdup_by_index(new_line, j, *i);
		//temp2 = omit_quotes(temp);
		//temp2 = omit_double_quote(temp);
		//temp2 = omit_single_quote(temp);
		*args = ft_strjoin_2dim_memdel(*args, malloc_args(temp));
		ft_memdel(&temp);
		ft_memdel(&temp2);
	}
	//(*i)++;
}

char	**split_readline_by_argc(t_minishell *msh, char **args, char *line)
{
	//char	**args;
	char	**temp_args;
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*new_line;
	size_t	argc;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	//args = NULL;
	temp = NULL;
	temp2 = NULL;
	new_line = NULL;
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
	while (i < size)
	{
		while (new_line[i] == ' ')
			i++;
		if (i == 0 && (new_line[i] == Q_SINGLE || new_line[i] == Q_DOUBLE))
		{
			fprintf(stderr, "qu string line[%zu]=%c\n", i, line[i]);
			split_quotes(&args, new_line, &i);
		}
		else if (i != 0 && (new_line[i - 1] != '\\' && (new_line[i] == Q_SINGLE || new_line[i] == Q_DOUBLE)))
		{
			fprintf(stderr, "qu string line[%zu]=%c\n", i, line[i]);
			split_quotes(&args, new_line, &i);
		}
/*
		if (new_line[i] == Q_SINGLE)
		{
			//i += check_single_quote((new_line + i + 1), &argc);
			j = i;
			i += check_single_quote((new_line + i + 1));
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
			//fprintf(stderr, "new_line[%zu]=%c\n", i - 1, new_line[i - 1]);
			//fprintf(stderr, "new_line[%zu]=%c\n", i, new_line[i]);
		}
		else if (new_line[i] == Q_DOUBLE)
		{
			j = i;
			i += check_double_quote((new_line + i + 1));
			temp = ft_strdup_by_index(new_line, j, i);
			//next_quote_i = check_double_quote(temp + 1, &argc);
			//temp2 = omit_character(temp, next_quote_i, Q_DOUBLE);
			//temp2 = omit_character(temp, Q_DOUBLE);
			temp2 = omit_quotes(temp);
			args = ft_strjoin_2dim_memdel(args, malloc_args(temp2));
			ft_memdel(&temp);
			ft_memdel(&temp2);
		}
*/
		else if (new_line[i] >= 33 && new_line[i] <= 126)
		{
			j = i;
			//while (new_line[i + 1] != Q_SINGLE && new_line[i + 1] != Q_DOUBLE && new_line[i + 1] != ' ' && new_line[i + 1] != '\0')
			//if (new_line[i] == Q_SINGLE || new_line[i] == Q_DOUBLE)
			//i++;
			{
				while (new_line[i + 1] != '\0')
				{
					if (new_line[i] != '\\' && (new_line[i + 1] == Q_SINGLE || new_line[i + 1] == Q_DOUBLE))
						break ;
					if (!((new_line[i + 1] != Q_SINGLE || new_line[i + 1] != Q_DOUBLE) && new_line[i + 1] != ' '))
						break ;
					i++;
				}
				fprintf(stderr, "af string line + %zu=%s\n", i, line + i);
				temp = ft_strdup_by_index(new_line, j, i);
			}
			i++;
			
			if (new_line[i] == Q_SINGLE)
			{
				j = i;
				(i) += check_single_quote((new_line + (i) + 1), 0);
				temp2 = ft_strdup_by_index(new_line, j, i);
				temp2 = ft_strjoin_memdel(temp, temp2);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp2));
			}
			else if (new_line[i] == Q_DOUBLE)
			{
				j = i;
				(i) += check_double_quote((new_line + (i) + 1), 0);
				temp2 = ft_strdup_by_index(new_line, j, i);
				temp2 = ft_strjoin_memdel(temp, temp2);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp2));
			}
			else
			{
				//temp = ft_strdup_by_index(new_line, j, i);
				//ft_memdel(&temp);
				//temp = omit_character(temp2, '\\');
				temp_args = split_character(malloc_args(temp), '|');
				ft_memdel(&temp);
				temp_args = split_character(temp_args, ';');
				temp_args = split_string(temp_args, "<<");
				temp_args = split_string(temp_args, ">>");
				temp_args = split_character(temp_args, '<');
				temp_args = split_character(temp_args, '>');
				args = ft_strjoin_2dim_memdel(args, temp_args);
			}
			print_2dim_string(args, ft_strlen_2dim((const char **)args));
			ft_memdel(&temp2);
		}
		//msh->cmd.args = ft_strjoin_2dim_memdel(msh->cmd.args, malloc_args(msh, ));
		i++;
	}
	ft_memdel(&new_line);
	return (args);
}
