/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_redirection_n.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:41:52 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:41:52 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_args(t_minishell *msh, t_cmd *cmd, char ***args)
{
	char	*temp;
	size_t	size;
	size_t	j;

	size = ft_strlen_2dim((const char **)*args);
	j = -1;
	temp = NULL;
	while (++j < size)
	{
		if ((!ft_strcmp((*args)[j], ">>") || !ft_strcmp((*args)[j], ">"))
			&& (ft_strchr((*args)[j + 1], '$')
				&& ft_strcmp((*args)[j + 1], "$")))
			temp = replace_variables(msh, (*args)[j + 1]);
		{
			if (temp != NULL && !ft_strcmp(temp, ""))
			{
				print_err_msg("msh: ",
					(*args)[j + 1], ": ambiguous redirect\n");
				ft_memdel(&temp);
				return (1);
			}
		}
	}
	ft_memdel(&temp);
	return (0);
}

char	**check_redirection_variable(t_minishell *msh, t_cmd *cmd, char **args)
{
	char	**temp_args;
	char	**new_args;
	char	**pipe_args;
	size_t	i;

	i = -1;
	new_args = NULL;
	while (++i < cmd->pipe_count + 1)
	{
		pipe_args = parse_pipe_part(args, i);
		if (check_pipe_args(msh, cmd, &pipe_args) == 1)
		{
			ft_memdel_2dim(&args);
			ft_memdel_2dim(&pipe_args);
			return ((char **) NULL);
		}
		if (i != cmd->pipe_count)
		{
			temp_args = malloc_args("|");
			pipe_args = ft_strjoin_2dim_memdel(pipe_args, temp_args);
		}
		new_args = ft_strjoin_2dim_memdel(new_args, pipe_args);
	}
	ft_memdel_2dim(&args);
	return (new_args);
}
