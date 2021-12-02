/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omit_quotes_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:48:03 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/02 01:48:03 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_quotes(t_flags *flags, char *str, size_t *c_count, size_t *i)
{
	if (flags->q_single == 0 && (*i == 0 && str[*i] == Q_DOUBLE))
	{
		flags->q_double = 1;
		(*c_count)++;
		(*i)++;
	}
	else if (flags->q_double == 0 && (*i == 0 && str[*i] == Q_SINGLE))
	{
		flags->q_single = 1;
		(*c_count)++;
		(*i)++;
	}
	else if (flags->q_single == 0 && flags->q_double == 0 && *i > 0
		&& (str[*i - 1] != '\\'
			&& (str[*i] == Q_DOUBLE || str[*i] == Q_SINGLE)))
	{
		if ((*i > 0 && str[*i - 1] != '\\') && str[*i] == Q_DOUBLE)
			flags->q_double = 1;
		else if ((*i > 0 && str[*i - 1] != '\\') && str[*i] == Q_SINGLE)
			flags->q_single = 1;
		(*c_count)++;
		(*i)++;
	}
}

static void	close_quotes(t_flags *flags, char *str, size_t *c_count, size_t *i)
{
	if (flags->q_double == 1 && str[*i] == Q_DOUBLE)
	{
		flags->q_double = 0;
		(*c_count)++;
		(*i)++;
	}
	else if (flags->q_single == 1 && str[*i] == Q_SINGLE)
	{
		flags->q_single = 0;
		(*c_count)++;
		(*i)++;
	}
}

static	char	*return_newline(t_flags *flags, char *str, size_t cnt, size_t i)
{
	char	*dst;
	size_t	j;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(str) - cnt + 1));
	if (!dst)
		return (NULL);
	j = 0;
	while (str[i] != '\0')
	{
		open_quotes(flags, str, &cnt, &i);
		if ((flags->q_double == 1 && str[i] == Q_DOUBLE)
			|| (flags->q_single == 1 && str[i] == Q_SINGLE))
			close_quotes(flags, str, &cnt, &i);
		else
			dst[j++] = str[i++];
	}
	dst[j] = '\0';
	return (dst);
}

char	*omit_quotes(char *str)
{
	t_flags	flags;
	size_t	i;
	size_t	c_count;

	if (ft_strlen(str) == 0)
		return (ft_strdup(""));
	i = 0;
	c_count = 0;
	init_flags(&flags);
	while (i < ft_strlen(str))
	{
		open_quotes(&flags, str, &c_count, &i);
		if ((flags.q_double == 1 && str[i] == Q_DOUBLE)
			|| (flags.q_single == 1 && str[i] == Q_SINGLE))
			close_quotes(&flags, str, &c_count, &i);
		else
			i++;
	}
	if (ft_strlen(str) - c_count == 0)
		return (ft_strdup(""));
	return (return_newline(&flags, str, c_count, 0));
}
