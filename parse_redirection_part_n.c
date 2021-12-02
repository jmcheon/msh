/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_part_n.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:49:56 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:49:57 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirection_part(t_minishell *msh, t_cmd *cmd, char ***pipe_args)
{
	size_t	size;
	size_t	i;

	i = -1;
	size = ft_strlen_2dim((const char **)*pipe_args);
	while (++i < size)
	{
		if ((!ft_strcmp((*pipe_args)[i], "<")))
		{
			if (redirect_input(msh, *pipe_args + i) == 1)
				cmd->valid_fd = -1;
			*pipe_args = ft_substr_2dim(pipe_args, i, 2);
			size -= 2;
			i--;
		}
		else if ((!ft_strcmp((*pipe_args)[i], ">"))
			|| (!ft_strcmp((*pipe_args)[i], ">>")))
		{
			if (redirect_output(msh, (*pipe_args)[i], (*pipe_args)[i + 1]) == 1)
				cmd->valid_fd = -1;
			*pipe_args = ft_substr_2dim(pipe_args, i, 2);
			size -= 2;
			i--;
		}
	}
}
