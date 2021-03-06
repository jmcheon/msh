/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:46:46 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:46:47 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_flags(t_flags *flags)
{
	flags->q_single = 0;
	flags->q_double = 0;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->args = NULL;
	cmd->temp_path = NULL;
	cmd->heredoc_paths = NULL;
	cmd->pipe_count = 0;
	cmd->valid_fd = 0;
}

void	init_msh(t_minishell *msh, char **envp)
{
	msh->ret = NULL;
	msh->envp = ft_strdup_2dim((const char **)envp);
	msh->stdfd[0] = dup(STDIN_FILENO);
	msh->stdfd[1] = dup(STDOUT_FILENO);
	msh->cmd_count = 1;
	msh->cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	init_cmd(&msh->cmd[0]);
}

void	free_cmd(t_cmd *cmd, int mode)
{
	size_t	i;

	i = 0;
	if (cmd->args != NULL)
		ft_memdel_2dim(&(cmd->args));
	if (cmd->heredoc_paths != NULL)
	{
		while (mode == 0
			&& i < ft_strlen_2dim((const char **)cmd->heredoc_paths))
			unlink(cmd->heredoc_paths[i++]);
		ft_memdel_2dim(&(cmd->heredoc_paths));
	}
	if (cmd->temp_path != NULL)
	{
		if (mode == 0)
			unlink(cmd->temp_path);
		ft_memdel(&(cmd->temp_path));
	}
}

void	free_msh(t_minishell *msh, int mode)
{
	int	i;

	i = 0;
	while (i < msh->cmd_count)
	{
		free_cmd(&msh->cmd[i], mode);
		free(&msh->cmd[i++]);
	}
	if (msh->ret != NULL)
		ft_memdel(&(msh->ret));
	ft_memdel_2dim(&msh->envp);
	close(msh->stdfd[0]);
	close(msh->stdfd[1]);
}
