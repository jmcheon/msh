/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2dim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:20:40 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:20:41 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_2dim(const char **args1)
{
	char	**dst_args;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen_2dim(args1);
	dst_args = (char **)malloc((size + 1) * sizeof(char *));
	if (!dst_args)
		return (NULL);
	while (i < size)
	{
		dst_args[i] = ft_strdup(args1[i]);
		i++;
	}
	dst_args[i] = NULL;
	return (dst_args);
}
