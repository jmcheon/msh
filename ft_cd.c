/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:25:54 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:25:55 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_pwd_variable(t_minishell *msh, char *variable)
{
	char	path[1024];
	char	*temp;
	char	*temp2;
	int		i;

	temp = NULL;
	temp2 = NULL;
	getcwd(path, 1024);
	i = search_one_variable_path(msh, variable);
	if (i >= 0)
	{
		temp = msh->envp[i];
		temp2 = ft_strjoin(variable, "=");
		msh->envp[i] = ft_strjoin(temp2, path);
		ft_memdel(&temp);
		ft_memdel(&temp2);
	}
}

static void	check_error_cd(t_minishell *msh, char **args, int err)
{
	if (err >= 0)
	{
		modify_pwd_variable(msh, "PWD");
		msh->exit_status = 0;
	}
	else
	{
		print_err_msg("msh: cd: ", args[1], ": ");
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		msh->exit_status = 1;
	}
}

void	ft_cd(t_minishell *msh, char **args, int err)
{
	char	*temp;
	char	*home_path;
	char	*old_path;

	home_path = search_one_variable(msh, "HOME");
	old_path = search_one_variable(msh, "OLDPWD");
	modify_pwd_variable(msh, "OLDPWD");
	if (args[1] == NULL)
		err = chdir(home_path);
	else if (args[1][0] == '-' && args[1][1] == '\0')
		err = chdir(old_path);
	else if (args[1][0] == '~' && (args[1][1] == '\0' || args[1][1] == '/'))
	{
		temp = ft_strjoin(home_path, args[1] + 1);
		err = chdir(temp);
		ft_memdel(&temp);
	}
	else
		err = chdir(args[1]);
	check_error_cd(msh, args, err);
	ft_memdel(&home_path);
	ft_memdel(&old_path);
}
