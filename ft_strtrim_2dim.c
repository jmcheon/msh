/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_2dim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:13:05 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:13:06 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	get_size(const char **args, const char *set)
{
	size_t	i;
	size_t	size;

	i = -1;
	size = 0;
	while (args[++i] != NULL)
	{
		if (!ft_strcmp(args[i], set))
			size++;
	}
	return (size);
}

char	**ft_strtrim_2dim(const char **args, const char *set)
{
	char	**dst_args;
	size_t	i;
	size_t	j;
	size_t	size;

	size = get_size(args, set);
	if (args == NULL)
		return (NULL);
	dst_args = (char **)malloc(sizeof(char *)
			* (ft_strlen_2dim(args) - size + 1));
	if (!dst_args)
		return ((char **) NULL);
	i = -1;
	j = 0;
	while (args[++i] != NULL)
	{
		if (ft_strcmp(args[i], set))
			dst_args[j++] = ft_strdup(args[i]);
	}
	dst_args[j] = NULL;
	return (dst_args);
}
