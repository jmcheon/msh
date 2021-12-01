/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_2dim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:12:42 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:12:43 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_substr_2dim(char ***args, size_t start, size_t len)
{
	char	**new_args;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen_2dim((const char **)*args) - len;
	new_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_args)
		return ((char **) NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (j == start)
		{
			while (len-- > 0)
				j++;
		}
		new_args[i++] = ft_strdup((*args)[j++]);
	}
	new_args[i] = NULL;
	ft_memdel_2dim(args);
	return (new_args);
}
