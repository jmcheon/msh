#include "minishell.h"

char	**malloc_args(char *str)
{
	char	**temp_args;

	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return ((char **) NULL);
	temp_args[0] = ft_strdup(str);
	temp_args[1] = NULL;
	return (temp_args);
}

char	**malloc_args_memdel(char *str)
{
	char	**temp_args;

	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return ((char **) NULL);
	temp_args[0] = ft_strdup(str);
	temp_args[1] = NULL;
	ft_memdel(&str);
	return (temp_args);
}
