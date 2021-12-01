/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_by_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:20:23 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:20:23 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_by_index(char *line, size_t start, size_t end)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!dst)
		return (NULL);
	while (start <= end)
		dst[i++] = line[start++];
	dst[i] = '\0';
	return (dst);
}
