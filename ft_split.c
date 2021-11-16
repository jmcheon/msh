/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:51:00 by cjung-mo          #+#    #+#             */
/*   Updated: 2019/12/11 02:45:53 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hm(char const *s, char c)
{
	size_t	nbr;
	size_t	i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (i > 0 && s[i] && s[i - 1] == c)
			nbr++;
		if (s[i])
			i++;
	}
	if (nbr == 0 && s[i - 1] == c)
		return (0);
	if (s[0] != c)
		nbr++;
	return (nbr);
}

static int	i_malloc_ft_mal(char **strs, size_t cnt, size_t ih[2])
{
	strs[ih[0]] = malloc(sizeof(char) * (cnt + 1));
	if (!strs[ih[0]])
		return (1);
	return (0);
}

static char	**ft_mal(char **strs, char const *s, char c)
{
	size_t	ih[2];
	size_t	cnt;

	cnt = 0;
	ih[0] = 0;
	ih[1] = 0;
	while (s[ih[1]])
	{
		if (s[ih[1]] != c)
			cnt++;
		else if (ih[1] > 0 && s[ih[1] - 1] != c)
		{
			if (i_malloc_ft_mal(strs, cnt, ih) == 1)
				return (0);
			cnt = 0;
			ih[0]++;
		}
		if (s[ih[1] + 1] == '\0' && s[ih[1]] != c)
		{
			if (i_malloc_ft_mal(strs, cnt, ih) == 1)
				return (0);
		}
		ih[1]++;
	}
	return (strs);
}

static void	i_copy(char **strs, char const *s, char c)
{
	size_t	h;
	size_t	i;
	size_t	j;

	h = 0;
	i = 0;
	j = 0;
	while (s[h])
	{
		if (s[h] != c)
			strs[i][j++] = s[h];
		else if (h > 0 && s[h - 1] != c)
		{
			if (h != 0)
			{
				strs[i][j] = '\0';
				j = 0;
				i++;
			}
		}
		if (s[h + 1] == '\0' && s[h] != c)
			strs[i][j] = '\0';
		h++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	nbr_w;

	if (!s || !*s)
	{
		ret = malloc(sizeof(char *) * 1);
		if (!ret)
			return (NULL);
		*ret = (void *)0;
		return (ret);
	}
	nbr_w = ft_hm(s, c);
	ret = malloc(sizeof(char *) * (nbr_w + 1));
	if (!ret)
		return (0);
	if (ft_mal(ret, s, c) != 0)
		i_copy(ret, s, c);
	else
	{
		ft_memdel(ret);
		return (NULL);
	}
	ret[nbr_w] = (void *)0;
	return (ret);
}
