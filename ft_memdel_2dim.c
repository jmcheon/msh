/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel_2dim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 01:27:26 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/09/13 01:27:27 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_memdel_2dim_old(char **str)
{
	int		i;
	int		len;

	i = 0;
	//printf("memdel 2dim=%s\n", *str);
	if (*str != NULL)
	{
		len = ft_strlen_2dim((const char **)str);
		//printf("len=%zu\n", len);
		while (i < len)
		{
		//	printf("str[%d]=%s\n", i, str[i]);
			if (str[i] != NULL)
				ft_memdel(&str[i]);
			i++;
			//free(str[i]);
			//str[i++] = NULL;
		}
		//printf("mtr[%d]=%s\n", i, str[i]);
		free(str);
		str = NULL;
	}
}
void	ft_memdel_2dim(char ***str)
{
	int		i;
	int		len;

	i = 0;
	if (*str != NULL)
	{
		len = ft_strlen_2dim((const char **)*str);
		//printf("len=%zu\n", len);
		//while (*str[i] != NULL)
		while (i < len)
		{
		//	printf("str[%d]=%s\n", i, str[i]);
			if ((*str + i) != NULL)
			{
				//fprintf(stderr, "str free=%s\n", *(*str + i));
				ft_memdel(*str + i);
			}
			i++;
			//free(str[i]);
			//str[i++] = NULL;
		}
		//printf("mtr[%d]=%s\n", i, str[i]);
		free(*str);
		*str = NULL;
	}
}
