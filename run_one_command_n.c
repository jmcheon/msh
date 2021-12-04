/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one_command_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:33:10 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/03 16:33:10 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_one_process(t_minishell *msh, t_cmd *cmd)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)cmd->args);
	parse_redirection_part(msh, cmd, &cmd->args);
	if (ft_issymbol(&cmd->args[0]) != 0)
	{
		ft_memdel_2dim(&cmd->args);
		cmd->args = NULL;
	}
	if (execute_one_command(msh, cmd, cmd->args) == 1)
		return (1);
	free_msh(msh, 1);
	exit(0);
}

static int	wait_child(void)
{
	int		wstatus;

	wait(&wstatus);
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == 2)
			return (130);
		else if (WTERMSIG(wstatus) == 3)
			return (131);
		else
			return (WIFSIGNALED(wstatus));
	}
	if (WEXITSTATUS(wstatus))
		return (WEXITSTATUS(wstatus));
	return (0);
}

int	run_one_command(t_minishell *msh, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return (1);
	}
	listen_signals_child();
	if (pid == 0)
	{
		if (run_one_process(msh, cmd) == 1)
		{
			if (msh->ret != NULL)
			{
				printf("one cmd:%s\n", msh->ret);
				ft_memdel(&msh->ret);
			}
			free_msh(msh, 1);
			exit (g_exit_status);
		}
		return (0);
	}
	return (wait_child());
}
