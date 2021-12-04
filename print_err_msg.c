/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:11:01 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/04 03:11:01 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_msg(char *msg, char *str, char *msg2)
{
	char	*temp;
	char	*temp2;

	if (str != NULL)
		temp = ft_strjoin(msg, str);
	else
		temp = ft_strdup(msg);
	temp2 = ft_strjoin(temp, msg2);
	write(STDERR_FILENO, temp2, ft_strlen(temp2));
	ft_memdel(&temp);
	ft_memdel(&temp2);
}
