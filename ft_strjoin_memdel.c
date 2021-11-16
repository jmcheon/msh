/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:43:50 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/11 02:46:28 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_memdel(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		len;

	i = -1;
	len = 0;
	//if (!s1 || !s2)
	//	return (NULL);
	dst = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[len])
	{
		dst[len] = s1[len];
		len++;
	}
	while (++i < (int)ft_strlen(s2))
		dst[len + i] = s2[i];
	dst[len + i] = 0;
	if (s1 != NULL)
		ft_memdel(&s1);
	if (s2 != NULL)
		ft_memdel(&s2);
	return (dst);
}
