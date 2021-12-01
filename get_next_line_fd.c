#include "get_next_line.h"


char	*get_line(char *str)
{
	char	*dest;
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	//printf("i:%d, l:%ld\n", i, ft_strlen(str));
	dest = (char *)malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] != 0 && str[i] != '\n')
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*next_str(char *str)
{
	char	*dest;
	int	i, j;

	
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	if (str[i + 1] == '\0')
	{
		printf("%c|\n", str[i + 1]);
	}
	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!dest)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	//printf("dest:%s|\n", dest);
	free(str);
	return (dest);
}

char	*get_next_line_fd(int fd)
{
	static char	*str;
	char	*line;
	//char	buf[BUFFER_SIZE + 1];
	char	*buf;
	char	*temp;
	int	nread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nread = 1;
	while (ft_strchr(str, '\n') == NULL && nread != 0)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nread] = '\0';
		if (str == NULL)
			temp = ft_strdup(buf);
		else	
			temp = ft_strjoin(str, buf);
		if (str != NULL)
			free(str);
		str = temp;
	}
	free(buf);
	if (!str)
		return (NULL);
	line = get_line(str);
	//str = next_str(str);
/*
	printf("str|| : |%s|\n", str);
	if (!str)
		printf("str is null : %s\n", str);
*/
	return (line);
}
