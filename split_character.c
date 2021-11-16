#include "minishell.h"

static size_t	get_character_count(char *str, int c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static char	**ft_split_character(char *str, int c)
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


char	**split_character(char **args, int c)
{
	char	*temp;
	char	**new_args;
	char	**temp_args;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	printf("split pipe character original str, size=%zu, c=%c\n", size, c);
	//print_2dim_string(args, ft_strlen_2dim((const char **)args));
	//printf("size=%zu\n", size);
	new_args = NULL;
	while (i < size)
	{
		//printf("args[%zu]=%s\n", i, args[i]);
		temp = ft_itos(c);
		if ((ft_strchr(args[i], c) && ft_strcmp(args[i], "<<") == 0)
			|| (ft_strchr(args[i], c) && ft_strcmp(args[i], ">>") == 0))
		{
			printf("fr\n");
			//temp_args = ft_split_pipe(args[i]);
			//new_args = ft_strjoin_2dim_memdel((const char **)new_args, (const char **)temp_args);
			temp_args = (char **)malloc(sizeof(char *) * 2);
			if (!temp_args)
				return ((char **)NULL);
			temp_args[0] = ft_strdup(args[i]);
			temp_args[1] = NULL;
			new_args = ft_strjoin_2dim_memdel(new_args, temp_args);
		}
		//else if (ft_strchr(args[i], c) && ft_strcmp(args[i], temp))
		else if (ft_strchr(args[i], c)
			&& (ft_strchr(args[i], c) - args[i] > 0 && (args[i][ft_strchr(args[i], c) - args[i] - 1] != '\\'))
			&& ft_strcmp(args[i], temp))
		{
			//printf("\\ch test s=%s\n", ft_strchr(args[i], c));
			//printf("\\ch test zu=%zu\n", ft_strchr(args[i], c) - args[i]);
			//printf("\\ch test=%c\n", args[i][ft_strchr(args[i], c) - args[i] - 1]);
			//fprintf(stderr, "split char args[%zu]=%s\n", i, args[i]);
			temp_args = ft_split_character(args[i], c);
			new_args = ft_strjoin_2dim_memdel(new_args, temp_args);
		}
		else
		{
			printf("lat\n");
			temp_args = (char **)malloc(sizeof(char *) * 2);
			if (!temp_args)
				return ((char **)NULL);
			temp_args[0] = ft_strdup(args[i]);
			temp_args[1] = NULL;
			new_args = ft_strjoin_2dim_memdel(new_args, temp_args);
		}
		free(temp);
		/*
		   if (ft_strchr(args[i], '|'))
		   printf("\tstrchr args[%zu]=%s\n", i, args[i]);
		if (!ft_strcmp(args[i], "|"))
			printf("\tstrcmp args[%zu]=%s\n", i, args[i]);
*/
		i++;
	}
	//printf("split pipe character after split, c=%c\n", c);
	//print_2dim_string(new_args, ft_strlen_2dim((const char **)new_args));
	ft_memdel_2dim(&args);
	//printf("return\n");
	return (new_args);
}
