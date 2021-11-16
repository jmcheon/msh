#include "get_next_line.h"

static void	get_line(char **str, char **temp, char **tp, char buf[])
{
	if (*str == NULL)
		*temp = ft_strdup(buf);
	else
		*temp = ft_strjoin(*str, buf);
	if (*str != NULL)
		free(*str);
	*str = *temp;
	*tp = ft_strchr(*str, '\n');
}

static void	next_line(char **str, char **temp, char **tp, char **line)
{
	*temp = *str;
	*line = ft_substr(*str, 0, *tp - *str);
	*str = ft_strdup(*tp + 1);
	free(*temp);
}

int	get_next_line(char **line)
{
	static char	*str;
	char		buf[1024];
	char		*temp;
	char		*tp;
	int			nread;

	nread = 1;
	tp = NULL;
	while (tp == NULL && nread != 0)
	{
		nread = read(0, buf, 1024);
		if (nread == -1)
			return (-1);
		buf[nread] = '\0';
		get_line(&str, &temp, &tp, buf);
	}
	if (tp != NULL)
	{
		next_line(&str, &temp, &tp, line);
		return (1);
	}
	*line = str;
	str = NULL;
	return (0);
}
