#include "minishell.h"

char	*search_one_variable(t_minishell *msh, char *variable)
{
	char	**args;
	char	*value;
	size_t	i;

	i = 0;
	fprintf(stderr, "variable=%s, len=%zu\n", variable, ft_strlen(variable));
	while (msh->envp[i] != NULL && ft_strncmp(msh->envp[i], variable, ft_strlen(variable)) != 0)
		i++;
	if (msh->envp[i] == NULL)
	{
		fprintf(stderr, "null i=%zu, envp[i]=%s\n", i, msh->envp[i]);
		return (NULL);
	}
	fprintf(stderr, "envp line=%s, ft_strncmp=%d\n", msh->envp[i], ft_strncmp(msh->envp[i], variable, ft_strlen(variable) != 0));
	args = ft_split(msh->envp[i], '=');
	fprintf(stderr, "args[0]=%s\n", args[0]);
	fprintf(stderr, "ft_strcmp(args[0]. var)=%d\n", ft_strcmp(args[0], variable));
	if (ft_strcmp(args[0], variable) != 0)
	{
		fprintf(stderr, "ft_strcmp(args[0]. var)=%d\n", ft_strcmp(args[0], variable));
		ft_memdel_2dim(&args);
		return (NULL);
	}
	value = ft_strdup(ft_strchr(msh->envp[i], '=') + 1);
	fprintf(stderr, "value=%s\n", value);
	ft_memdel_2dim(&args);
	return (value);
}

static	size_t	get_next_split_index(char *line, int c)
{
	size_t	i;

	i = 0;
	//fprintf(stderr, "get next index line=%s\n", line);
	if (c == 0)
	{
		while (i < ft_strlen(line))
		{
			if (line[i] == Q_SINGLE || line[i] == Q_DOUBLE)
				break ;
			i++;
		}
	}
	else
	{
		while (i < ft_strlen(line))
		{
			if (line[i] == c)
				break ;
			i++;
		}
	}
	return (i);
}

char	**split_quotes_variable(t_minishell *msh, char *line)
{
	char	**args;
	//char	*temp;
	size_t	i;
	size_t	j;

	i = -1;
	args = NULL;
	//temp = NULL;
	while (++i < ft_strlen(line))
	{
		if (line[i] == Q_SINGLE || line[i] == Q_DOUBLE)
		{
			j = i;
			i += get_next_split_index(line + i + 1, line[i]) + 1;	
			fprintf(stderr, "split single quote variable line + %zu=%s\n", i, line + i);
			if (i - j == 1)
				continue ;
		}
		else
		{
			j = i;
			i += get_next_split_index(line + i + 1, 0);
			fprintf(stderr, "split variable line + %zu=%s\n", i, line + i);
		}
		//temp = ft_strdup_by_index(line, j, i);
		args = ft_strjoin_2dim_memdel(args, malloc_args_memdel(ft_strdup_by_index(line, j, i)));
		//ft_memdel(&temp);
	}
	return (args);
}

static size_t	get_next_variable_index(char **new_line, char *line)
{
	t_flags	flags;
	char	*temp;
	size_t	j;
	size_t	last_index;

	j = 0;
	temp = NULL;
	last_index = ft_strlen(*new_line);
	init_flags(&flags);
	fprintf(stderr, "next var index line=%s, new_line=%s\n", line, *new_line);
	if ((line)[0] == Q_SINGLE)
	{
		temp = ft_strdup(line);
		(*new_line) = ft_strjoin_memdel((*new_line), temp);
		return (ft_strlen(line));
	}
	else if ((line)[0] == Q_DOUBLE)
	{
		fprintf(stderr, "temp=%s\n", line);
		//while ((*line)[j] != '\0' && !((*line)[j] == '$' && (ft_isalnum((*line)[j + 1]) || (*line)[j + 1] == '_')))
		//while ((*line)[j] != '\0' && !((*line)[j] == '$' && (ft_isalnum((*line)[j + 1]) || (*line)[j + 1] == '_' || (*line)[j + 1] == '?')))
		//	(*new_line) = ft_strjoin_memdel((*new_line), ft_itos((*line)[j++]));
		while ((line)[j] != '\0' && !((line)[j] == '$' && (ft_isalnum((line)[j + 1]) || (line)[j + 1] == '_' || (line)[j + 1] == '?')))
			(*new_line) = ft_strjoin_memdel((*new_line), ft_itos((line)[j++]));
		j++;
	}
	else
	{
		while ((line)[j] != '\0' && !((line)[j] == '$' && (ft_isalnum((line)[j + 1]) || (line)[j + 1] == '_' || (line)[j + 1] == '?')))
			(*new_line) = ft_strjoin_memdel((*new_line), ft_itos((line)[j++]));
		j++;
	}
	return (j);
}

static size_t	get_next_variable_index_quote(char *line)
{
	size_t	i;

	i = 0;
	while ((line)[i] != '\0')
	{
		if (line[i + 1] == '\'' || line[i + 1] == '$' || line[i + 1] == ' ' || line[i + 1] == '\n')
			break ;
		if (line[i + 1] == '\"' || line[i + 1] == '|' || line[i + 1] == '<' || line[i + 1] == '>' || line[i + 1] == ';')
			break ;
		i++;
	}
	//fprintf(stderr, "gnv iq=%zu\n", i);
	return (i);
}

char	*replace_variables_one_line(t_minishell *msh, char *line)
{
	char	*new_line;
	char	*temp;
	char	*var;
	size_t	i;
	size_t	j;

	temp = NULL;
	new_line = NULL;
	var = NULL;
	//printf("var=%s\n", ft_strchr(line, '$'));
	new_line= (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	new_line[0] = '\0';
	j = 0;
	i = 0;
	while (i < ft_strlen(line))
	{
		i += get_next_variable_index(&new_line, (line + i));
		if (i >= ft_strlen(line))
			break ;
		fprintf(stderr, "line + %zu=%s\n", i, line + i);
		if (ft_strchr(line + i, '\"') != NULL || ft_strchr(line + i, '$') != NULL)
		{
			j = i;
			//fprintf(stderr, "line + (ft_strchr(line + j, '\"') - line)=%s\n", *line + (ft_strchr(*line + i, '\"') - *line));
			//fprintf(stderr, "(ft_strchr(line + j, '\"') - line)=%ld\n", (ft_strchr(*line + i, '\"') - *line));
			i += get_next_variable_index_quote(line + i);
			if ((line)[i] == '?')
			{
				fprintf(stderr, "exit status=%d\n", msh->exit_status);
				new_line = ft_strjoin_memdel(new_line, ft_itoa(msh->exit_status));
				fprintf(stderr, "new line=%s\n", new_line);
				i++;
				continue ;
				//return (new_line);
			}
			else
				temp = ft_strdup_by_index(line, j, i++); 
			//temp = ft_strdup_by_index(*line, i, ft_strchr(*line + i, '\"') - *line - 1);
		}
		else if ((line)[i] == '?')
		{
			fprintf(stderr, "exit status=%d\n", msh->exit_status);
			new_line = ft_strjoin_memdel(new_line, ft_itoa(msh->exit_status));
			fprintf(stderr, "new line=%s\n", new_line);
			//return (new_line);
			i++;
			continue ;
		}
		else
		{
			temp = ft_strdup(line + i);
			i += ft_strlen(temp);
		}
		fprintf(stderr, "temp=%s\n", temp);
		var = search_one_variable(msh, temp);
		ft_memdel(&temp);
		fprintf(stderr, "var=%s\n", var);
		new_line = ft_strjoin_memdel(new_line, var);
		fprintf(stderr, "with var=%s\n", new_line);
		if (line[i] == Q_SINGLE)
			new_line = ft_strjoin_memdel(new_line, ft_itos(line[i++]));
	}
	fprintf(stderr, "new var line=%s\n", new_line);
	//ft_memdel(&new_line); 
	ft_memdel(&temp); //ft_memdel(&var);
	temp = omit_quotes(new_line);
	//(new_line) = ft_strjoin_memdel((new_line), omit_quotes(new_line));
	ft_memdel(&new_line);
	return (temp);
}

char	*replace_variables(t_minishell *msh, char *line)
{
	char	**args;
	char	*new_line;
	char	*temp;
	size_t	j;

	temp = NULL;
	new_line = ft_strdup("");
	fprintf(stderr, "replace var\n");
	args = split_quotes_variable(msh, line);
	j = 0;
	while (j < ft_strlen_2dim((const char **)args))
	{
		temp = args[j];
		args[j] = replace_variables_one_line(msh, args[j]);
		ft_memdel(&temp);
		j++;
	}
	j = 0;
	while (j < ft_strlen_2dim((const char **)args))
	{
		new_line = ft_strjoin_memdel(new_line, ft_strdup(args[j]));
		j++;
	}
	ft_memdel_2dim(&args);
	fprintf(stderr, "replace var new line=%s\n", new_line);
	return (new_line);
}

void	check_variables(t_minishell *msh, char ***args)
{
	char	**new_args;
	char	*temp;
	size_t	size;
	size_t	i;

	i = 0;
	temp = NULL;
	size = ft_strlen_2dim((const char **)*args);
	while (i < size)
	{
		temp = (*args)[i];
		if (ft_strchr((*args)[i], '$') && ft_strcmp((*args)[i], "$"))
		{
			(*args)[i] = replace_variables(msh, (*args)[i]);
			if (!ft_strcmp((*args)[i], ""))
			{
				new_args = *args;
				*args = ft_strtrim_2dim_by_index((const char **)new_args, i, i);
				ft_memdel_2dim(&new_args);
			}
		}
		else
			(*args)[i] = omit_quotes((*args)[i]);
		ft_memdel(&temp);
		i++;
	}
	//new_args = ft_strtrim_2dim((const char **)*args, "");
	//ft_memdel_2dim(args);
	//ft_memdel(&temp);
	//return (new_args);
}

