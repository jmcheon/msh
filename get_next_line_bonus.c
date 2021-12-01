/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:54:30 by cjung-mo          #+#    #+#             */
/*   Updated: 2020/02/01 22:03:36 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_check_error(char **line, char *str, int ret)
{
	if (ret < 0)
		return (GNL_ERR);
	else if (str == NULL && ret == 0)
	{
		*line = ft_strdup("");
		ft_memdel(line);
		return (GNL_EOF);
	}
	return (GNL_EOL);
}

static char	*ft_read_doc(int fd, char **str, char *buf, int *ret)
{
	char	*temp;
	int		start;

	start = 0;
	while (*ret > 0 || start == 0)
	{
		start = 1;
		*ret = read(fd, buf, BUFFER_SIZE);
		buf[*ret] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(str[fd], buf);
			ft_memdel(&str[fd]);
			str[fd] = temp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (str[fd]);
}

static char	*ft_strmod(char *str, int i)
{
	char		*temp;

	temp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	ft_memdel(&str);
	str = temp;
	return (str);
}

static int	i_gnl(char **line, char *str[1024], int i, int fd)
{
	if (str[fd][i] == '\n')
	{
		*line = ft_substr(str[fd], 0, i);
		str[fd] = ft_strmod(str[fd], i);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		ft_memdel(&str[fd]);
		return (GNL_EOF);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[1024];
	char		buf[BUFFER_SIZE + 1];
	int			i;
	int			ret;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0 || !line)
		return (GNL_ERR);
	str[fd] = ft_read_doc(fd, str, buf, &ret);
	if (ft_check_error(*&line, str[fd], ret) < 1)
		return (ft_check_error(*&line, *str, ret));
	while (str[fd][i] != '\n' && str[fd][i])
		i++;
	if (i_gnl(line, str, i, fd) == GNL_EOF)
		return (GNL_EOF);
	if (str[fd] != NULL)
		ft_memdel(&str[fd]);
	return (GNL_EOL);
}
