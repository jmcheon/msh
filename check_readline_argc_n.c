/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_readline_argc_n.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:45:37 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:45:38 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_single_quote(char *line, size_t i)
{
	while (line[i] != Q_SINGLE && line[i] != '\0')
		i++;
	i++;
	if (line[i] != '\0' && line[i] != ' '
		&& line[i] != Q_DOUBLE && line[i] != Q_SINGLE)
	{
		if (line[i] >= 33 && line[i] <= 126)
		{
			while (line[i + 1] != '\0')
			{
				if ((line[i] != '\\'
						&& (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
					|| (!((line[i + 1] != Q_SINGLE || line[i + 1] != Q_DOUBLE)
							&& line[i + 1] != ' ')))
					break ;
				i++;
			}
		}
		i++;
	}
	if (line[i] == Q_DOUBLE)
		i += check_double_quote((line + i + 1), 0) + 1;
	if (line[i] != '\0' && line[i] == Q_SINGLE)
		i += check_single_quote((line + i + 1), 0) + 1;
	return (i);
}

size_t	check_double_quote(char *line, size_t i)
{
	while (line[i] != Q_DOUBLE && line[i] != '\0')
		i++;
	i++;
	if (line[i] != '\0' && line[i] != ' '
		&& line[i] != Q_DOUBLE && line[i] != Q_SINGLE)
	{
		if (line[i] != Q_DOUBLE && line[i] >= 33 && line[i] <= 126)
		{
			while (line[i + 1] != '\0')
			{
				if ((line[i] != '\\'
						&& (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
					|| (!((line[i + 1] != Q_SINGLE || line[i + 1] != Q_DOUBLE)
							&& line[i + 1] != ' ')))
					break ;
				i++;
			}
		}
		i++;
	}
	if (line[i] == Q_SINGLE)
		i += check_single_quote((line + i + 1), 0) + 1;
	if (line[i] != '\0' && line[i] == Q_DOUBLE)
		i += check_double_quote((line + i + 1), 0) + 1;
	return (i);
}

static void	split_quotes(char *line, size_t *argc, size_t *i)
{
	(*argc)++;
	if (line[*i] == Q_SINGLE)
		(*i) += check_single_quote((line + (*i) + 1), 0);
	else if (line[*i] == Q_DOUBLE)
		(*i) += check_double_quote((line + (*i) + 1), 0);
}

static size_t	split_line(char *line, size_t *argc, size_t i)
{
	(*argc)++;
	while (line[i + 1] != '\0')
	{
		if (line[i] != '\\'
			&& (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
			break ;
		if (!((line[i + 1] != Q_SINGLE || line[i + 1] != Q_DOUBLE)
				&& line[i + 1] != ' '))
			break ;
		i++;
	}
	i++;
	if (line[i] == Q_SINGLE || line[i] == Q_DOUBLE)
		split_quotes(line, argc, &i);
	return (i);
}

size_t	check_readline_argc(char *line)
{
	size_t	argc;
	size_t	i;
	size_t	size;

	size = ft_strlen(line);
	i = 0;
	argc = 0;
	while (i < size)
	{
		while (line[i] == ' ')
			i++;
		if (i == 0 && (line[i] == Q_SINGLE || line[i] == Q_DOUBLE))
			split_quotes(line, &argc, &i);
		else if (i > 0 && (line[i - 1] != '\\'
				&& (line[i] == Q_SINGLE || line[i] == Q_DOUBLE)))
			split_quotes(line, &argc, &i);
		else if (line[i] >= 33 && line[i] <= 126)
			i = split_line(line, &argc, i);
		i++;
	}
	return (argc);
}
