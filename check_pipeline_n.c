/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipeline_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:52:54 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 16:52:55 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	check_last_character(char *line)
{
	size_t	i;
	size_t	last;

	i = 0;
	while (i < ft_strlen(line))
	{
		while (line[i] == ' ')
			i++;
		if ((line[i] >= 33 && line[i] <= 126))
		{
			while (line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
			last = i;
		}
		i++;
	}
	return (last);
}

int	check_pipeline(t_minishell *msh, char **line)
{
	size_t	i;
	size_t	argc;
	int		err;

	i = 0;
	err = check_readline_syntax_error(msh, *line);
	if (err == 2)
		return (2);
	else if (err == 1)
		return (1);
	argc = check_readline_argc(*line);
	if (argc > 0)
	{
		if ((*line)[check_last_character(*line) - 1] != '\\'
			&& (*line)[check_last_character(*line)] == '|')
		{
			printf("msh: syntax error near unexpected token '|'\n");
			return (2);
		}
	}
	return (0);
}
