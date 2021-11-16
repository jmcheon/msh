/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:31:36 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/09/09 16:31:37 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	i_ft_execve(char *cmd, char **args, unsigned int i)
{
	char	**paths;
	char	*current_path;
	char	*new_path;

	paths = ft_split(environ[i] + 5, ':');
	i = 0;
	while (i < ft_strlen_2dim((const char **)paths))
	{
		current_path = ft_strjoin(paths[i], "/");
		new_path = ft_strjoin(current_path, cmd);
		execve(new_path, args, environ);
		free(current_path);
		free(new_path);
		i++;
	}
	ft_memdel_2dim(paths);
}

void	ft_execve(char *cmd, char **args, char **ret)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
			i_ft_execve(cmd, args, i);
		i++;
	}
	*ret = ft_strjoin(cmd, ": command not found\n");
}
