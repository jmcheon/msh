
#include "libft.h"

char	**ft_strjoin_2dim(const char **args1, const char **args2)
{
	char	**dst_args;
	int		i;
	int		j;
	int		len;
	int		args1_size;
	int		args2_size;

	len = 0;
	j = 0;
	args1_size = ft_strlen_2dim(args1);
	args2_size = ft_strlen_2dim(args2);
	if (!*args1 || !*args2)
		return (NULL);
	dst_args = (char **)malloc((args1_size + args2_size + 1) * sizeof(char *));
	if (!dst_args)
		return (NULL);
	i = 0;
	while (i < args1_size)
	{
		dst_args[j++] = ft_strdup(args1[i]);
		i++;
	}
	i = 0;
	while (i < args2_size)
	{
		dst_args[j++] = ft_strdup(args2[i]);
		i++;
	}
	dst_args[j] = NULL;
	return (dst_args);
}
