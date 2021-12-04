/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:44:54 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/01 13:44:55 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static size_t	get_string_count(char *str, char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_strncmp(str + i, s, ft_strlen(s)) == 0)
		{
			count++;
			i += ft_strlen(s) - 1;
		}
		i++;
	}
	return (count);
}

static size_t	get_new_size(char *str, char *s)
{
	size_t	size;

	size = (get_string_count(str, s) * 2) + 1;
	if ((ft_strcmp(str + (ft_strlen(str) - ft_strlen(s)), s) == 0)
		&& str[(ft_strlen(str) - ft_strlen(s) - 1)] != s[0])
		size--;
	if (ft_strncmp(str, s, ft_strlen(s)) == 0)
		size--;
	return (size);
}

static void	i_ft_split_string(char ***dst_args, char **str, size_t *i, char *s)
{
	char	*temp;
	size_t	j;
	size_t	temp_length;

	temp = ft_strstr(*str, s);
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
		(*dst_args)[*i] = ft_strdup(s);
		*str += ft_strlen(s);
	}
}

static char	**ft_split_string(char *str, char *s)
{
	char	**dst_args;
	size_t	i;
	size_t	size;

	size = get_new_size(str, s);
	dst_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dst_args)
		return ((char **) NULL);
	i = 0;
	while (*str)
	{
		i_ft_split_string(&dst_args, &str, &i, s);
		i++;
	}
	dst_args[i] = NULL;
	return (dst_args);
}

char	**split_string(char **args, char *s)
{
	char	**new_args;
	size_t	i;

	i = 0;
	new_args = NULL;
	while (i < ft_strlen_2dim((const char **)args))
	{
		if (ft_strstr(args[i], s)
			&& (ft_strstr(args[i], s) - args[i] > 0
				&& (args[i][ft_strstr(args[i], s) - args[i] - 1] != '\\'))
			&& ft_strcmp(args[i], s))
			new_args = ft_strjoin_2dim_memdel(new_args,
					ft_split_string(args[i], s));
		else
			new_args = ft_strjoin_2dim_memdel(new_args, malloc_args(args[i]));
		i++;
	}
	ft_memdel_2dim(&args);
	return (new_args);
}
