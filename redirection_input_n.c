/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:31:24 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/03 16:31:24 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *token, char *infile_path, int *infile)
{
	char	*temp_path;

	temp_path = NULL;
	if (!ft_strcmp(token, "<<"))
	{
		temp_path = ft_strjoin(HEREDOC_PATH, infile_path);
		*infile = open(temp_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	else
		*infile = open(infile_path, O_RDONLY);
	if (*infile == -1)
	{
		ft_memdel(&temp_path);
		return (1);
	}
	ft_memdel(&temp_path);
	return (0);
}

static void	i_get_next_heredoc(t_minishell *msh,
			char **args, char *temp, int infile)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!ft_strcmp(line, temp))
			{
				ft_memdel(&line);
				break ;
			}
			check_variables(msh, &args);
			write(infile, line, ft_strlen(line));
			write(infile, "\n", 1);
			ft_memdel(&line);
		}
		else
		{
			ft_memdel(&line);
			break ;
		}
		ft_memdel(&line);
	}
}

static int	get_next_heredoc(t_minishell *msh, t_cmd *cmd,
			char **args, int infile)
{
	char	*temp;

	temp = NULL;
	if (!ft_strcmp(args[0], "<<"))
	{
		ft_memdel(&cmd->temp_path);
		temp = omit_quotes(args[1]);
		cmd->temp_path = ft_strjoin(HEREDOC_PATH, temp);
		g_exit_status = 0;
		listen_signals_heredoc();
		i_get_next_heredoc(msh, args, temp, infile);
		dup2(msh->stdfd[0], STDIN_FILENO);
		dup2(msh->stdfd[1], STDOUT_FILENO);
		close(msh->stdfd[0]);
		close(msh->stdfd[1]);
		msh->stdfd[0] = dup(STDIN_FILENO);
		msh->stdfd[1] = dup(STDOUT_FILENO);
		ft_memdel(&temp);
		if (g_exit_status == 130)
			return (1);
	}
	return (0);
}

int	execute_heredoc(t_minishell *msh, t_cmd *cmd, char **args)
{
	char	*temp_path;
	char	*temp;
	int		infile;

	temp = NULL;
	temp_path = omit_quotes(args[1]);
	if (open_infile(args[0], temp_path, &infile) == 1)
	{
		if (msh->ret == NULL)
		{
			temp = ft_strjoin(temp_path, ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
			g_exit_status = 1;
		}
		return (1);
	}
	ft_memdel(&temp_path);
	if (get_next_heredoc(msh, cmd, args, infile) == 1)
		return (1);
	return (0);
}

int	redirect_input(t_minishell *msh, char **args)
{
	char	*temp;
	int		infile;

	temp = NULL;
	if (open_infile(args[0], args[1], &infile) == 1)
	{
		if (msh->ret == NULL)
		{
			temp = ft_strjoin(args[1], ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
			g_exit_status = 1;
		}
		return (1);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (0);
}
