/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmalloc_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:45:21 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:45:21 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_line2(char *line, char **dst, size_t *j, size_t *i)
{
	(*dst)[(*j)++] = ' ';
	(*dst)[(*j)++] = line[(*i)++];
	(*dst)[(*j)++] = line[(*i)++];
	(*dst)[(*j)++] = ' ';
}

static void	new_line(char *line, char **dst, size_t *j, size_t *i)
{
	(*dst)[(*j)++] = ' ';
	(*dst)[(*j)++] = line[(*i)++];
	(*dst)[(*j)++] = ' ';
}

static size_t	i1_rmalloc_line(char *line, char **dst, size_t *j, size_t i)
{
	if (line[i] == Q_SINGLE)
	{
		(*dst)[(*j)++] = line[i++];
		while (line[i] != Q_SINGLE && line[i] != '\0')
			(*dst)[(*j)++] = line[i++];
		(*dst)[(*j)++] = line[i++];
	}
	else if (line[i] == Q_DOUBLE)
	{
		(*dst)[(*j)++] = line[i++];
		while (line[i] != Q_DOUBLE && line[i] != '\0')
			(*dst)[(*j)++] = line[i++];
		(*dst)[(*j)++] = line[i++];
	}
	return (i);
}

static void	i2_rmalloc_line(char *line, char **dst, size_t *j, size_t *i)
{
	if (*i == 0 && ((line[*i] == '<' && line[*i + 1] == '<')
			|| (line[*i] == '>' && line[*i + 1] == '>')))
		new_line2(line, dst, j, i);
	else if (*i == 0 && (line[*i] == '|'
			|| line[*i] == '>' || line[*i] == '<'))
		new_line(line, dst, j, i);
	if (*i > 0 && line[*i - 1] != '\\'
		&& ((line[*i] == '<' && line[*i + 1] == '<')
			|| (line[*i] == '>' && line[*i + 1] == '>')))
		new_line2(line, dst, j, i);
	else if (*i > 0 && line[*i - 1] != '\\' && (line[*i] == '|'
			|| line[*i] == '>' || line[*i] == '<'))
		new_line(line, dst, j, i);
	else
	{
		if ((*i > 0 && line[*i - 1] == '\\')
			&& ((line[*i] == '<' && line[*i + 1] == '<')
				|| (line[*i] == '>' && line[*i + 1] == '>')))
		{
			(*dst)[(*j)++] = line[(*i)++];
			(*dst)[(*j)++] = line[(*i)++];
		}
		else if (line[*i] != '\0')
			(*dst)[(*j)++] = line[(*i)++];
	}
}

char	*rmalloc_line(char *line, size_t size)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size <= 0)
		return (ft_strdup(line));
	dst = (char *)malloc(sizeof(char) * (ft_strlen(line) + size + 1));
	if (!dst)
		return (NULL);
	while (i < ft_strlen(line))
	{
		i = i1_rmalloc_line(line, &dst, &j, i);
		i2_rmalloc_line(line, &dst, &j, &i);
	}
	dst[j] = '\0';
	return (dst);
}
