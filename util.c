/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:13:20 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/04 03:13:20 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iscommand(char **s)
{
	size_t	i;

	i = 0;
	if (*s == NULL || **s == '\0')
		return (-1);
	while ((*s)[i])
	{
		if (ft_isalnum((*s)[i]) == 0 && ((*s)[i] != '/' || (*s)[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_issymbol(char **s)
{
	size_t	i;

	i = 0;
	if (*s == NULL)
		return (-1);
	if (!ft_strcmp(*s, "<") || !ft_strcmp(*s, ">") || !ft_strcmp(*s, "<<")
		|| !ft_strcmp(*s, ">>") || !ft_strcmp(*s, "|") || !ft_strcmp(*s, ";"))
		return (1);
	return (0);
}
