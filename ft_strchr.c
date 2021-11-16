/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:04:20 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/07 00:20:42 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	if ((char)c == '\0')
	{
		while (*str)
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str++ == (char)c)
			return ((char *)--str);
	}
	return (NULL);
}
