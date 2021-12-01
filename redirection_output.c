/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:45:49 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:45:51 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_outfile(char *token, char *outfile_path, int *outfile)
{
	if (!ft_strcmp(token, ">>"))
		*outfile = open(outfile_path, O_RDWR | O_CREAT | O_APPEND, 0664);
	else
		*outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*outfile == -1)
		return (1);
	return (0);
}

int	redirect_output(t_minishell *msh, char *token, char *outfile_path)
{
	char	*temp;
	int		outfile;

	temp = NULL;
	if (msh->cmd[0].valid_fd == -1)
	{
		msh->cmd[0].valid_fd = 0;
		return (1);
	}
	if (open_outfile(token, outfile_path, &outfile) == 1)
	{
		if (msh->ret == NULL)
		{
			temp = ft_strjoin(outfile_path, ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
		}
		return (1);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (0);
}
