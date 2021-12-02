/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:45:12 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:45:13 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	get_next_split_index(char *line, int c)
{
	size_t	i;

	i = 0;
	if (c == 0)
	{
		while (i < ft_strlen(line))
		{
			if (line[i] == Q_SINGLE || line[i] == Q_DOUBLE)
				break ;
			i++;
		}
	}
	else
	{
		while (i < ft_strlen(line))
		{
			if (line[i] == c)
				break ;
			i++;
		}
	}
	return (i);
}

static char	**split_quotes_variable(t_minishell *msh, char *line, size_t i)
{
	char	**args;
	char	*temp;
	size_t	j;

	args = NULL;
	temp = NULL;
	while (++i < ft_strlen(line))
	{
		if (line[i] == Q_SINGLE || line[i] == Q_DOUBLE)
		{
			j = i;
			i += get_next_split_index(line + i + 1, line[i]) + 1;
			if (i - j == 1)
				continue ;
		}
		else
		{
			j = i;
			i += get_next_split_index(line + i + 1, 0);
		}
		temp = ft_strdup_by_index(line, j, i);
		args = ft_strjoin_2dim_memdel(args, malloc_args_memdel(temp));
	}
	return (args);
}

static char	*delete_one_dollor_before_quotes(t_minishell *msh, char *line)
{
	char	*new_line;
	size_t	i;

	i = 0;
	new_line = malloc_by_size(ft_strlen(line));
	while (i < ft_strlen(line))
	{
		if (line[i] == '$'
			&& (line[i + 1] == Q_SINGLE || line[i + 1] == Q_DOUBLE))
			;
		else
			new_line = ft_strjoin_memdel(new_line, ft_itos((line)[i]));
		i++;
	}
	return (new_line);
}

char	*replace_variables(t_minishell *msh, char *line)
{
	char	**args;
	char	*new_line;
	char	*temp;
	size_t	j;

	new_line = ft_strdup("");
	temp = delete_one_dollor_before_quotes(msh, line);
	args = split_quotes_variable(msh, temp, -1);
	ft_memdel(&temp);
	j = 0;
	while (j < ft_strlen_2dim((const char **)args))
	{
		temp = args[j];
		args[j] = replace_variables_one_line(msh, args[j]);
		ft_memdel(&temp);
		j++;
	}
	j = 0;
	while (j < ft_strlen_2dim((const char **)args))
	{
		new_line = ft_strjoin_memdel(new_line, ft_strdup(args[j]));
		j++;
	}
	ft_memdel_2dim(&args);
	return (new_line);
}

void	check_variables(t_minishell *msh, char ***args)
{
	char	**tmp_args;
	char	*temp;
	size_t	i;

	i = -1;
	while (++i < ft_strlen_2dim((const char **)*args))
	{
		temp = (*args)[i];
		if (ft_strchr((*args)[i], '$') && ft_strcmp((*args)[i], "$")
			&& !ft_strstr((*args)[i], HEREDOC_PATH))
		{
			(*args)[i] = replace_variables(msh, (*args)[i]);
			if (!ft_strcmp((*args)[i], ""))
			{
				tmp_args = *args;
				*args = ft_strtrim_2dim_by_index((const char **)tmp_args, i, i);
				ft_memdel_2dim(&tmp_args);
			}
		}
		else if (ft_strstr((*args)[i], HEREDOC_PATH))
			(*args)[i] = ft_strdup((*args)[i]);
		else
			(*args)[i] = omit_quotes((*args)[i]);
		ft_memdel(&temp);
	}
}
