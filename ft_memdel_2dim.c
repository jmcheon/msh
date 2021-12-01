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

void	ft_memdel_2dim(char ***str)
{
	int		i;
	int		len;

	i = 0;
	if (*str != NULL)
	{
		len = ft_strlen_2dim((const char **)*str);
		while (i < len)
		{
			if ((*str + i) != NULL)
				ft_memdel(*str + i);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}
