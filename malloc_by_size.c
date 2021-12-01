#include "minishell.h"

char	*malloc_by_size(size_t size)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	return (dst);
}
