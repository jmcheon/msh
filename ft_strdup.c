/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:46:53 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/02 15:45:14 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s1[size])
		size++;
	dst = (char *)malloc((size + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < size)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
