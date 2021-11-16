/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:55:25 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/11 02:41:24 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start_idx(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		match_flag;

	i = 0;
	while (s1 != NULL && i < (int)ft_strlen(s1))
	{
		j = 0;
		match_flag = 0;
		while (j < (int)ft_strlen(set))
		{
			if (s1[i] == set[j])
				match_flag = 1;
			j++;
		}
		if (match_flag == 0)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_find_last_idx(const char *s1, const char *set, int start)
{
	int		i;
	int		j;
	int		match_flag;
	int		last;

	i = start;
	while (s1 != NULL && i < (int)ft_strlen(s1))
	{
		j = 0;
		match_flag = 0;
		while (j < (int)ft_strlen(set))
		{
			if (s1[i] == set[j])
				match_flag = 1;
			j++;
		}
		if (match_flag == 1 && s1[i])
			match_flag = 0;
		else if (match_flag == 0)
			last = i;
		i++;
	}
	return (last);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*dst;
	int		i;
	int		start;
	int		last;

	i = 0;
	start = ft_find_start_idx(s1, set);
	last = ft_find_last_idx(s1, set, start);
	if (s1 == NULL)
		return (NULL);
	if (start > last)
		start = last + 1;
	dst = (char *)malloc((last - start + 2) * sizeof(char));
	if (!dst)
		return (NULL);
	while (start <= last)
	{
		dst[i++] = s1[start];
		start++;
	}
	dst[i] = '\0';
	return (dst);
}
