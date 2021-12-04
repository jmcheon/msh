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
	size_t	length;
	int		i;

	i = 0;
	length = ft_strlen(variable);
	while (msh->envp[i] != NULL)
	{
		if (ft_strncmp(msh->envp[i], variable, length) == 0
			&& (msh->envp[i][length] == '=' || msh->envp[i][length] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*search_one_variable(t_minishell *msh, char *variable)
{
	char	*value;
	int		i;

	i = search_one_variable_path(msh, variable);
	value = NULL;
	if ((i >= 0 && msh->envp[i] == NULL) || i < 0)
		return (NULL);
	if (msh->envp[i][ft_strlen(variable)] == '=')
		value = ft_strdup(ft_strchr(msh->envp[i], '=') + 1);
	return (value);
}
