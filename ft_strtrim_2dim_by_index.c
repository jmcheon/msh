/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_2dim_by_index.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:15:40 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:15:42 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strtrim_2dim_by_index(const char **args, size_t start, size_t end)
{
	char	**dst_args;
	size_t	i;
	size_t	j;

	i = -1;
	if (args == NULL)
		return (NULL);
	dst_args = (char **)malloc(sizeof(char *)
			* (ft_strlen_2dim(args) - (end - start + 1) + 1));
	if (!dst_args)
		return ((char **) NULL);
	i = -1;
	j = 0;
	while (args[++i] != NULL)
	{
		if (i < start || i > end)
			dst_args[j++] = ft_strdup(args[i]);
	}
	dst_args[j] = NULL;
	return (dst_args);
}
