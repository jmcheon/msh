/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_readline_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:44:34 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:44:35 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_quotes(char ***args, char *line, char *temp_line, size_t *i)
{
	char	*temp;
	char	*temp2;
	size_t	j;

	temp = NULL;
	temp2 = NULL;
	j = *i;
	if (line[*i] == Q_SINGLE)
		(*i) += check_single_quote((line + (*i) + 1), 0);
	else if (line[*i] == Q_DOUBLE)
		(*i) += check_double_quote((line + (*i) + 1), 0);
	temp = ft_strdup_by_index(line, j, *i);
	if (temp_line == NULL)
		*args = ft_strjoin_2dim_memdel(*args, malloc_args(temp));
	else
	{
		temp2 = ft_strjoin(temp_line, temp);
		*args = ft_strjoin_2dim_memdel(*args, malloc_args(temp2));
	}
	ft_memdel(&temp);
	ft_memdel(&temp2);
}

static void	split_line_symbol(char ***args, char *new_line, char *temp)
{
	char	**temp_args;

	temp_args = NULL;
	temp_args = split_character(malloc_args(temp), '|');
	temp_args = split_string(temp_args, "<<");
	temp_args = split_string(temp_args, ">>");
	temp_args = split_character(temp_args, '<');
	temp_args = split_character(temp_args, '>');
	*args = ft_strjoin_2dim_memdel(*args, temp_args);
}

static size_t	split_line(char ***args, char *new_line, size_t i)
{
	char	*temp;
	size_t	j;

	j = i;
	temp = NULL;
	while (new_line[i + 1] != '\0')
	{
		if (new_line[i] != '\\'
			&& (new_line[i + 1] == Q_SINGLE || new_line[i + 1] == Q_DOUBLE))
			break ;
		if (!((new_line[i + 1] != Q_SINGLE || new_line[i + 1] != Q_DOUBLE)
				&& new_line[i + 1] != ' '))
			break ;
		i++;
	}
	temp = ft_strdup_by_index(new_line, j, i);
	i++;
	if (new_line[i] == Q_SINGLE || new_line[i] == Q_DOUBLE)
		split_quotes(args, new_line, temp, &i);
	else
		split_line_symbol(args, new_line, temp);
	ft_memdel(&temp);
	return (i);
}

char	**split_readline_by_argc(t_minishell *msh, char **args, char *line)
{
	char	*new_line;
	size_t	i;
	size_t	size;

	i = -1;
	if (check_readline_argc(line) > 0)
	{
		new_line = rmalloc_line(line, get_new_line_size(line));
		size = ft_strlen(new_line);
	}
	while (++i < size)
	{
		while (new_line[i] == ' ')
			i++;
		if (i == 0 && (new_line[i] == Q_SINGLE || new_line[i] == Q_DOUBLE))
			split_quotes(&args, new_line, NULL, &i);
		else if (i != 0 && (new_line[i - 1] != '\\'
				&& (new_line[i] == Q_SINGLE || new_line[i] == Q_DOUBLE)))
			split_quotes(&args, new_line, NULL, &i);
		else if (new_line[i] >= 33 && new_line[i] <= 126)
			i = split_line(&args, new_line, i);
	}
	ft_memdel(&new_line);
	return (args);
}
