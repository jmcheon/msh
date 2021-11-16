#include "minishell.h" 

static size_t	get_string_count(char *str, char *s)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_strncmp(str + i, s, ft_strlen(s)) == 0)
		{
			count++;
			i += ft_strlen(s) - 1;
		}
		i++;
	}
	return (count);
}

static char	**ft_split_string(char *str, char *s)
{
	char	**dst_args;
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	temp_length;
	size_t	size;

	size = (get_string_count(str, s) * 2) + 1;
	if ((ft_strcmp(str + (ft_strlen(str) - ft_strlen(s)), s) == 0) && str[(ft_strlen(str) - ft_strlen(s) - 1)] != s[0])
		size--;
	if (ft_strncmp(str, s, ft_strlen(s)) == 0)
		size--;
	//printf("split string size=%zu\n", size);
	dst_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dst_args)
		return ((char **)NULL);
	i = 0;
	while (*str)
	{
		temp = ft_strstr(str, s);
		if (temp == NULL)
		{
			//printf("temp is null\n");
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
			dst_args[i] = ft_strdup(s); 
			str += ft_strlen(s);
		}
		i++;
	}
	dst_args[i] = NULL;
	return (dst_args);
}
char	**split_string(char **args, char *s)
{
	char	*temp;
	char	**new_args;
	char	**temp_args;
	size_t	i;
	size_t	size;

	i = 0;
	//printf("split string original str, s=%s\n", s);
	size = ft_strlen_2dim((const char **)args);
	//print_2dim_string(args, ft_strlen_2dim((const char **)args));
	//printf("size=%zu\n", size);
	new_args = NULL;
	while (i < size)
	{
		//if (ft_strchr(args[i], c) && ft_strcmp(args[i], temp))
		//if (ft_strstr(args[i], s) && ft_strcmp(args[i], s))
		if (ft_strstr(args[i], s) && args[i][ft_strstr(args[i], s) - args[i] - 1] != '\\' && ft_strcmp(args[i], s))
		{
		//	printf("args[i]=%s\n", args[i]);
			temp_args = ft_split_string(args[i], s);
			new_args = ft_strjoin_2dim_memdel(new_args, temp_args);
		}
		else
		{
			temp_args = (char **)malloc(sizeof(char *) * 2);
			if (!temp_args)
				return ((char **)NULL);
			temp_args[0] = ft_strdup(args[i]);
			temp_args[1] = NULL;
			new_args = ft_strjoin_2dim_memdel(new_args, temp_args);
		}
		i++;
	}
	//printf("split string after split, s=%s\n", s);
	//print_2dim_string(new_args, ft_strlen_2dim((const char **)new_args));
	ft_memdel_2dim(&args);
	//printf("return\n");
	return (new_args);
}
