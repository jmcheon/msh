/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:36:39 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:36:40 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_minishell *msh, char *path, char *var, char *value)
{
	char	*temp;
	int		n;
	int		mode;

	n = search_one_variable_path(msh, var);
	mode = (path[ft_strlen(var)] == '+' && path[ft_strlen(var) + 1] == '=');
	if (n >= 0)
	{
		temp = msh->envp[n];
		if (mode == 1)
			msh->envp[n] = ft_strjoin(msh->envp[n], value);
		else
			msh->envp[n] = ft_strjoin_memdel(ft_strdup(var),
					ft_strjoin("=", value));
	}
	else
	{
		if (mode == 1)
			temp = ft_strjoin_memdel(ft_strdup(var), ft_strjoin("=", value));
		else
			temp = ft_strdup(path);
		msh->envp = ft_strjoin_2dim_memdel(msh->envp, malloc_args(temp));
	}
	ft_memdel(&temp);
}
