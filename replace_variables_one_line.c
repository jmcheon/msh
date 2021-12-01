/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables_one_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:44:09 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:44:09 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_next_variable_index(char **new_line, char *line)
{
	size_t	j;

	j = 0;
	if ((line)[0] == Q_SINGLE)
	{
		(*new_line) = ft_strjoin_memdel((*new_line), ft_strdup(line));
		return (ft_strlen(line));
	}
	else
	{
		while (line[j] != '\0' && !(line[j] == '$' && (ft_isalnum(line[j + 1])
					|| line[j + 1] == '_' || line[j + 1] == '?')))
			(*new_line) = ft_strjoin_memdel((*new_line), ft_itos((line)[j++]));
		j++;
	}
	return (j);
}

static size_t	get_next_variable_index_quote(char *line)
{
	size_t	i;

	i = 0;
	while ((line)[i] != '\0')
	{
		if (line[i + 1] == '\'' || line[i + 1] == '$'
			|| line[i + 1] == ' ' || line[i + 1] == '\n')
			break ;
		if (line[i + 1] == '\"' || line[i + 1] == '|' || line[i + 1] == '<'
			|| line[i + 1] == '>' || line[i + 1] == ';')
			break ;
		i++;
	}
	return (i);
}

static char	*get_variable(char *line, size_t *i)
{
	char	*temp;
	size_t	j;

	temp = NULL;
	if (ft_strchr(line + *i, '\"') || ft_strchr(line + *i, '$'))
	{
		j = *i;
		*i += get_next_variable_index_quote(line + *i);
		temp = ft_strdup_by_index(line, j, (*i)++);
	}
	else
	{
		temp = ft_strdup(line + *i);
		*i += ft_strlen(temp);
	}
	return (temp);
}

static int	check_loop(char **new_line, char *line, size_t *i, int exit_status)
{
	size_t	j;

	if (ft_strchr(line + *i, '\"') || ft_strchr(line + *i, '$'))
	{
		j = *i;
		*i += get_next_variable_index_quote(line + *i);
		if (line[*i] == '?')
		{
			*new_line = ft_strjoin_memdel(*new_line, ft_itoa(exit_status));
			(*i)++;
			return (1);
		}
		else
			*i = j;
	}
	else if (line[*i] == '?')
	{
		*new_line = ft_strjoin_memdel(*new_line, ft_itoa(exit_status));
		(*i)++;
		return (1);
	}
	return (0);
}

char	*replace_variables_one_line(t_minishell *msh, char *line)
{
	char	*new_line;
	char	*temp;
	size_t	i;

	temp = NULL;
	new_line = malloc_by_size(ft_strlen(line));
	i = 0;
	while (i < ft_strlen(line))
	{
		i += get_next_variable_index(&new_line, (line + i));
		if (i >= ft_strlen(line))
			break ;
		if (check_loop(&new_line, line, &i, msh->exit_status) == 1)
			continue ;
		else
			temp = get_variable(line, &i);
		new_line = ft_strjoin_memdel(new_line, search_one_variable(msh, temp));
		if (line[i] == Q_SINGLE)
			new_line = ft_strjoin_memdel(new_line, ft_itos(line[i++]));
		ft_memdel(&temp);
	}
	temp = omit_quotes(new_line);
	ft_memdel(&new_line);
	return (temp);
}
