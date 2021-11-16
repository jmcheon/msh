#include "minishell.h"

static size_t	check_next_single_quote(char *line, size_t *argc)
{
	size_t	i;

	i = 0;
	fprintf(stderr, " split char q single line=%s\n", line);
	if (line[i] == Q_SINGLE)
		return (1);
	while (line[i] != Q_SINGLE && line[i] != '\0') 
		i++;
	i++;
	return (i);
}

static size_t	get_quote_str_count(char *str, int c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == Q_SINGLE)
		{
			//	argc++;
			//i += check_single_quote((line + i + 1), &argc);
			j = i;
			i += check_single_quote((str + i + 1));
/*
			if (j + 1 == i)
			{
				temp = ft_strdup_by_index(str, j, i);
				args = ft_strjoin_2dim_memdel(args, malloc_args(temp));
				ft_memdel(&temp);
			}
*/
		}
	}
	return (count);
}

static char	**ft_split_quotes(char *str, int c)
{
	char	**dst_args;
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	temp_length;
	size_t	size;

	size = (get_character_count(str, c) * 2) + 1;
	if (str[ft_strlen(str) - 1] == c)
		size--;
	if (str[0] == c)
		size--;
	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == c)
			size--;
		i++;
	}
	dst_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dst_args)
		return ((char **)NULL);
	i = 0;
	while (i < size)
	{
		temp = ft_strchr(str, c);
		if (temp == NULL)
		{
			temp = str;
			temp_length = ft_strlen(temp);
		}
		else
			temp_length = temp - str;
		//printf("temp=%s\n", temp);
		//printf("temp_length =%ld\n", temp_length);
		if (temp_length != 0)
		{
			dst_args[i] = (char *)malloc(sizeof(char) * (temp_length + 1));
			if (!dst_args[i])
				return ((char **)NULL);
			j = 0;
			while (j < temp_length)
				dst_args[i][j++] = *str++;
			dst_args[i][j] = '\0';
		}
		else
		{
			temp = ft_itos(c);
			//dst_args[i] = ft_strdup("|"); 
			dst_args[i] = ft_strdup(temp); 
			free(temp);
			str++;
		}
		i++;
	}
	dst_args[i] = NULL;
	return (dst_args);
}
