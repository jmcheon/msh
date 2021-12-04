/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_pipe_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:32:49 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/03 16:32:49 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_child_pipe_commands(t_minishell *msh,
			t_cmd *cmd, int i, int (*pipefd)[2])
{
	char	**pipe_args;
	int		j;

	j = -1;
	while (++j < cmd->pipe_count)
	{
		if (j != i)
			close(pipefd[j][1]);
		if (j != i - 1)
			close(pipefd[j][0]);
	}
	pipe_args = parse_pipe_part(cmd->args, i);
	if (i == 0)
		return (run_pipein_process(msh, cmd, &pipe_args, pipefd[i]));
	else if (i == cmd->pipe_count)
	{
		redirect_pipeout(pipefd[i - 1]);
		return (run_pipeout_process(msh, cmd, &pipe_args));
	}
	else
	{
		redirect_pipe(pipefd[i - 1], pipefd[i]);
		return (run_pipe_process(msh, cmd, &pipe_args));
	}
	return (0);
}
