
#include "libft.h"

char	**ft_strjoin_2dim_memdel(char **args1, char **args2)
{
	char	**dst_args;
	int		i;
	int		j;
	int		args1_size;
	int		args2_size;

	args1_size = ft_strlen_2dim((const char **)args1);
	args2_size = ft_strlen_2dim((const char **)args2);
	//printf("args1 size=%d, args2 size=%d\n", args1_size, args2_size);
	//if (!*args1 || !*args2)
	//	return (NULL);
	dst_args = (char **)malloc((args1_size + args2_size + 1) * sizeof(char *));
	if (!dst_args)
		return (NULL);
	i = 0;
	j = 0;
	while (i < args1_size)
	{
		//printf("args1 while\n");
		dst_args[j++] = ft_strdup(args1[i]);
		i++;
	}
	i = 0;
	while (i < args2_size)
	{
		//printf("args2 while %s\n", args2[i]);
		dst_args[j++] = ft_strdup(args2[i]);
		i++;
	}
	dst_args[j] = NULL;
	if (args1 != NULL)
		ft_memdel_2dim((char ***)&args1);
	if (args2 != NULL)
		ft_memdel_2dim((char ***)&args2);
	return (dst_args);
}
