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

#include "minishell.h"

static int	i_ft_execve(t_minishell *msh, char **args, size_t *i)
{
	*i = 0;
	while (msh->envp[*i] != NULL
		&& ft_strncmp(msh->envp[*i], "PATH", 4) != 0)
		(*i)++;
	if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_cd(msh, args, 0);
		return (1);
	}
	if (ft_strcmp(args[0], "exit") == 0)
	{
		msh->exit_status = ft_exit_pipe(msh, args);
		return (1);
	}
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(msh));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(msh, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(msh));
	return (0);
}

int	ft_execve(t_minishell *msh, char **args)
{
	char	**paths;
	char	*new_path;
	char	*current_path;
	size_t	i;

	if (i_ft_execve(msh, args, &i) == 1)
		return (1);
	if (msh->envp[i] != NULL)
	{
		paths = ft_split(msh->envp[i] + 5, ':');
		i = -1;
		while (++i < ft_strlen_2dim((const char **)paths))
		{
			current_path = ft_strjoin(paths[i], "/");
			new_path = ft_strjoin(current_path, args[0]);
			execve(new_path, args, msh->envp);
			free(current_path);
			free(new_path);
		}
		ft_memdel_2dim(&paths);
	}
	msh->ret = ft_strjoin(args[0], ": command not found");
	msh->exit_status = 127;
	return (0);
}
