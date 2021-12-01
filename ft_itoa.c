/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:30:31 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/10 21:32:39 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n)
{
	int		len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	temp;
	long	i;
	char	*s;

	i = ft_len(n);
	temp = n;
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		temp = temp * (-1);
	}
	if (n == 0)
		s[0] = '0';
	s[i] = 0;
	while (temp >= 1 && i >= 0)
	{
		s[--i] = (temp % 10) + '0';
		temp /= 10;
	}
	return (s);
}
