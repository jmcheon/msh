/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:11:26 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/04 03:11:26 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

char	**check_valid_readline(t_minishell *msh, char *line)
{
	char	**args;

	args = NULL;
	args = split_readline_by_argc(args, line);
	if (args == NULL)
		return ((char **) NULL);
	msh->cmd[0].pipe_count = check_pipe_count(args, -1);
	args = check_redirection_variable(msh, &msh->cmd[0], args);
	if (args == NULL)
		return ((char **) NULL);
	args = check_valid_redirection(msh, &msh->cmd[0], args);
	check_variables(msh, &args);
	return (args);
}

int	run_readline(t_minishell *msh)
{
	if (msh->cmd[0].args == NULL)
	{
		free_cmd(&msh->cmd[0], 0);
		return (1);
	}
	if (msh->cmd[0].pipe_count)
		g_exit_status = run_pipe_commands(msh,
				&msh->cmd[0], msh->cmd[0].pipe_count);
	else if (ft_strcmp(msh->cmd[0].args[0], "cd") == 0)
		ft_cd(msh, msh->cmd[0].args, 0);
	else if (ft_strcmp(msh->cmd[0].args[0], "unset") == 0)
		ft_unset(msh, msh->cmd[0].args);
	else if (ft_strcmp(msh->cmd[0].args[0], "exit") == 0)
		g_exit_status = ft_exit(msh, msh->cmd[0].args);
	else if (ft_strcmp(msh->cmd[0].args[0], "export") == 0)
		ft_export(msh, msh->cmd[0].args);
	else
		g_exit_status = run_one_command(msh, &msh->cmd[0]);
	free_cmd(&msh->cmd[0], 0);
	return (0);
}

int	check_readline(t_minishell *msh, char **line)
{
	int	err;

	err = check_quotes(msh, line);
	if (err == 1)
		return (1);
	else if (err == 2)
	{
		g_exit_status = 2;
		return (1);
	}
	err = check_pipeline(msh, line);
	if (err == 1)
		return (1);
	else if (err == 2)
	{
		g_exit_status = 2;
		return (1);
	}
	msh->cmd[0].args = check_valid_readline(msh, *line);
	return (run_readline(msh));
}

int	ft_readline(t_minishell *msh)
{
	char	*line;
	char	*temp;

	while (1)
	{
		listen_signals();
		line = readline("minishell$ ");
		if (line)
		{
			check_readline(msh, &line);
			if (msh->ret != NULL)
			{
				ft_memdel(&line);
				return (1);
			}
		}
		else
			break ;
		if (check_readline_quotes(&temp, line) == 0)
			add_history(line);
		ft_memdel(&line);
		ft_memdel(&temp);
	}
	ft_memdel(&line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	msh;

	(void)argc;
	(void)argv;
	init_msh(&msh, envp);
	g_exit_status = 0;
	ft_readline(&msh);
	if (msh.ret != NULL)
	{
		printf("%s\n", msh.ret);
		ft_memdel(&msh.ret);
		free_msh(&msh, 0);
		return (1);
	}
	free_msh(&msh, 0);
	return (0);
}
