/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:55:14 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 16:55:15 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote_characters(t_flags *flags, char *line, size_t i)
{
	while (i < ft_strlen(line))
	{
		if (flags->q_double == 1 && line[i] == Q_DOUBLE)
		{
			flags->q_double = 0;
			i++;
		}
		else if (flags->q_single == 1 && line[i] == Q_SINGLE)
		{
			flags->q_single = 0;
			i++;
		}
		if (flags->q_single == 0 && (i == 0 && line[i] == Q_DOUBLE))
			flags->q_double = 1;
		else if (flags->q_double == 0 && (i == 0 && line[i] == Q_SINGLE))
			flags->q_single = 1;
		else if (flags->q_single == 0
			&& (i > 0 && line[i - 1] != '\\') && line[i] == Q_DOUBLE)
			flags->q_double = 1;
		else if (flags->q_double == 0
			&& (i > 0 && line[i - 1] != '\\') && line[i] == Q_SINGLE)
			flags->q_single = 1;
		i++;
	}
}

int	check_quotes(t_minishell *msh, char **line)
{
	t_flags	flags;
	int		err;

	err = check_readline_syntax_error(msh, *line);
	if (err == 2)
		return (2);
	else if (err == 1)
		return (1);
	init_flags(&flags);
	check_quote_characters(&flags, *line, 0);
	if (flags.q_single == 1 || flags.q_double == 1)
	{
		printf("msh: syntax error near unexpected token quotes\n");
		err = 2;
	}
	return (err);
}
