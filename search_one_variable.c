/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_one_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:43:58 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:43:59 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_one_variable_path(t_minishell *msh, char *variable)
{
	char	**args;
	size_t	i;

	i = 0;
	args = NULL;
	while (msh->envp[i] != NULL
		&& ft_strncmp(msh->envp[i], variable, ft_strlen(variable)) != 0)
		i++;
	if (msh->envp[i] == NULL)
		return (-1);
	if (!ft_strncmp(msh->envp[i], variable, ft_strlen(variable)))
	{
		if (msh->envp[i][ft_strlen(variable) + 1] == '=')
		{
			args = ft_split(msh->envp[i], '=');
			if (ft_strcmp(args[0], variable) != 0)
			{
				ft_memdel_2dim(&args);
				return (-1);
			}
		}
	}
	ft_memdel_2dim(&args);
	return (i);
}

char	*search_one_variable(t_minishell *msh, char *variable)
{
	char	**args;
	char	*value;
	size_t	i;

	i = 0;
	value = NULL;
	while (msh->envp[i] != NULL
		&& ft_strncmp(msh->envp[i], variable, ft_strlen(variable)) != 0)
		i++;
	if (msh->envp[i] == NULL)
		return (NULL);
	if (!ft_strncmp(msh->envp[i], variable, ft_strlen(variable)))
	{
		if (msh->envp[i][ft_strlen(variable) + 1] == '=')
		{
			args = ft_split(msh->envp[i], '=');
			if (ft_strcmp(args[0], variable) != 0)
			{
				ft_memdel_2dim(&args);
				return (NULL);
			}
		}
	}
	if (msh->envp[i][ft_strlen(variable) + 1] == '=')
		value = ft_strdup(ft_strchr(msh->envp[i], '=') + 1);
	ft_memdel_2dim(&args);
	return (value);
}
