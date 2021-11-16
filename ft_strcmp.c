/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:36:41 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/09 04:51:23 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (s1 == NULL)
	{
		//printf("s1 is null, s2=%s, %d\n", s2, *s2);
		return (*s2);
	}
	if (s2 == NULL)
		return (*s1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str2[i] != str1[i])
			break ;
		i++;
	}
	//printf("\ts1 - s2=%d\n", str1[i]-str2[i]);
	return (str1[i] - str2[i]);
}
