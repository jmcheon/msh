/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:44:21 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:44:21 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	i_get_new_line_size(char *line, size_t *size, size_t i)
{
	if ((i > 0 && line[i - 1] != '\\')
		&& ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')))
	{
		*size += 2;
		i += 2;
	}
	if ((i > 0 && line[i - 1] != '\\') && (line[i] == '|'
			|| line[i] == '>' || line[i] == '<'))
		*size += 2;
	if (i == 0 && ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')))
	{
		*size += 2;
		i += 2;
	}
	if (i == 0 && (line[i] == '|'
			|| line[i] == '>' || line[i] == '<'))
		*size += 2;
	return (i);
}

size_t	get_new_line_size(char *line)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == Q_SINGLE)
		{
			while (line[i + 1] != Q_SINGLE && line[i + 1] != '\0')
				i++;
			i++;
		}
		if (line[i] == Q_DOUBLE)
		{
			while (line[i + 1] != Q_DOUBLE && line[i + 1] != '\0')
				i++;
			i++;
		}
		i = i_get_new_line_size(line, &size, i);
		i++;
	}
	return (size);
}
