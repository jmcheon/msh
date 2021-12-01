/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_character_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:44:42 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:44:43 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_character_count(char *str, int c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static size_t	get_new_size(char *str, int c)
{
	size_t	i;
	size_t	size;

	size = (get_character_count(str, c) * 2) + 1;
	if (str[ft_strlen(str) - 1] == c)
		size--;
	if (str[0] == c)
		size--;
	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == c)
			size--;
		i++;
	}
	return (size);
}

static void	i_ft_split_character(char ***dst_args, char **str, size_t *i, int c)
{
	char	*temp;
	size_t	j;
	size_t	temp_length;

	temp = ft_strchr(*str, c);
	if (temp == NULL)
	{
		temp = *str;
		temp_length = ft_strlen(temp);
	}
	else
		temp_length = temp - *str;
	if (temp_length != 0)
	{
		(*dst_args)[*i] = malloc_by_size(temp_length);
		j = 0;
		while (j < temp_length)
			(*dst_args)[*i][j++] = *(*str)++;
		(*dst_args)[*i][j] = '\0';
	}
	else
	{
		(*dst_args)[*i] = ft_strjoin_memdel(NULL, ft_itos(c));
		(*str)++;
	}
}

static char	**ft_split_character(char *str, int c)
{
	char	**dst_args;
	size_t	i;
	size_t	size;

	size = get_new_size(str, c);
	dst_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dst_args)
		return ((char **) NULL);
	i = -1;
	while (++i < size)
		i_ft_split_character(&dst_args, &str, &i, c);
	dst_args[i] = NULL;
	return (dst_args);
}

char	**split_character(char **args, int c)
{
	char	*temp;
	char	**new_args;
	size_t	i;

	i = 0;
	new_args = NULL;
	while (i < ft_strlen_2dim((const char **)args))
	{
		temp = ft_itos(c);
		if ((ft_strchr(args[i], c) && ft_strcmp(args[i], "<<") == 0)
			|| (ft_strchr(args[i], c) && ft_strcmp(args[i], ">>") == 0))
			new_args = ft_strjoin_2dim_memdel(new_args, malloc_args(args[i]));
		else if (ft_strchr(args[i], c)
			&& (ft_strchr(args[i], c) - args[i] > 0
				&& (args[i][ft_strchr(args[i], c) - args[i] - 1] != '\\'))
			&& ft_strcmp(args[i], temp))
			new_args = ft_strjoin_2dim_memdel(new_args,
					ft_split_character(args[i], c));
		else
			new_args = ft_strjoin_2dim_memdel(new_args, malloc_args(args[i]));
		ft_memdel(&temp);
		i++;
	}
	ft_memdel_2dim(&args);
	return (new_args);
}
