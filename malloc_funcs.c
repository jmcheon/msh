/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:39:09 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:39:10 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_args(char *str)
{
	char	**temp_args;

	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return ((char **) NULL);
	temp_args[0] = ft_strdup(str);
	temp_args[1] = NULL;
	return (temp_args);
}

char	**malloc_args_memdel(char *str)
{
	char	**temp_args;

	temp_args = (char **)malloc(sizeof(char *) * 2);
	if (!temp_args)
		return ((char **) NULL);
	temp_args[0] = ft_strdup(str);
	temp_args[1] = NULL;
	ft_memdel(&str);
	return (temp_args);
}

char	*malloc_by_size(size_t size)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	return (dst);
}
