/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:05:40 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/03 17:05:40 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_execve(t_minishell *msh, char **args)
{
	char	*temp;

	temp = NULL;
	if (execve(args[0], args, msh->envp) == -1)
	{
		ft_memdel(&msh->ret);
		temp = ft_strjoin(args[0], ": ");
		msh->ret = ft_strjoin(temp, strerror(errno));
		ft_memdel(&temp);
		g_exit_status = 127;
	}
}

int	execute_one_command(t_minishell *msh, t_cmd *cmd, char **args)
{
	if (cmd->valid_fd < 0)
		cmd->valid_fd = 0;
	else if (args != NULL && (args[0][0] == '/'
		|| (args[0][0] == '.' && args[0][1] == '/')
		|| (args[0][0] == '.' && args[0][1] == '.' && args[0][2] == '/')))
		run_execve(msh, args);
	else if (args != NULL)
	{
		if (ft_execve(msh, args) == 1)
			return (1);
		if (g_exit_status != 0 && msh->ret == NULL)
			return (1);
	}
	else
	{
		dup2(msh->stdfd[0], STDIN_FILENO);
		dup2(msh->stdfd[1], STDOUT_FILENO);
	}
	if (msh->ret != NULL)
	{
		dup2(msh->stdfd[0], STDIN_FILENO);
		dup2(msh->stdfd[1], STDOUT_FILENO);
		return (1);
	}
	return (0);
}
