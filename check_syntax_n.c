/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:39:36 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:39:37 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_syntax_error(t_minishell *msh, char *s, int i)
{
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return (1);
	}
	if (pid == 0)
	{
		ft_memdel(&msh->ret);
		if (i == -3)
			msh->ret = ft_strdup("msh: error: unexpected token 'new line'");
		else if (i == -4)
			printf("msh: syntax error: unexpected end of file (wanted %s)\n", s);
		else
			msh->ret = ft_strjoin("msh: error near unexpected token ", s);
		return (1);
	}
	wait(&wstatus);
	if (WEXITSTATUS(wstatus))
		return (1);
	return (0);
}

static int	i_check_syntax_error(t_minishell *msh, char **args, size_t i)
{
	if ((!ft_strcmp(args[0], ";")
			|| (!ft_strcmp(args[i], ";") && !ft_strcmp(args[i - 1], ";")))
		|| (!ft_strcmp(args[i], ";") && !ft_strcmp(args[i + 1], ";")))
	{
		if (execute_syntax_error(msh, "';'", -1) == 1)
		{
			ft_memdel_2dim(&args);
			return (1);
		}
	}
	if ((!ft_strcmp(args[0], "|")
			|| (!ft_strcmp(args[i], "|") && !ft_strcmp(args[i - 1], "|")))
		|| (!ft_strcmp(args[i], "|") && !ft_strcmp(args[i + 1], "|")))
	{
		if (execute_syntax_error(msh, "'|'", -1) == 1)
		{
			ft_memdel_2dim(&args);
			return (1);
		}
	}
	return (0);
}

int	check_syntax_error(t_minishell *msh, char **args, size_t size)
{
	size_t	i;
	int		err;

	i = 0;
	err = 0;
	while (i < size)
	{
		if (i_check_syntax_error(msh, args, i) == 1)
			return (1);
		if ((!ft_strcmp(args[i], "<<")) || (!ft_strcmp(args[i], "<"))
			|| (!ft_strcmp(args[i], ">")) || (!ft_strcmp(args[i], ">>")))
		{
			if (ft_issymbol(&args[i + 1]) == 1)
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, args[i], -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_readline_quotes(char **temp, char *line)
{
	t_flags	flags;

	*temp = NULL;
	init_flags(&flags);
	check_quote_characters(&flags, line, 0);
	if (flags.q_single == 1)
		*temp = ft_strjoin(line, "\'");
	else if (flags.q_double == 1)
		*temp = ft_strjoin(line, "\"");
	else
		*temp = ft_strdup(line);
	if (check_readline_argc(*temp) <= 0)
	{
		ft_memdel(temp);
		return (1);
	}
	return (0);
}

int	check_readline_syntax_error(t_minishell *msh, char *line)
{
	char	*temp;
	char	**args;

	args = NULL;
	temp = NULL;
	if (check_readline_quotes(&temp, line) == 1)
		return (1);
	args = split_readline_by_argc(args, temp);
	ft_memdel(&temp);
	if (check_syntax_error(msh, args, ft_strlen_2dim((const char **)args)) == 1)
		return (2);
	ft_memdel_2dim(&args);
	return (0);
}
