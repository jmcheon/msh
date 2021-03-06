/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:25:45 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:25:45 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	i_ft_echo(char **cmd, int i)
{
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[++i])
			write(1, " ", 1);
	}
}

int	ft_echo(char **cmd)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j])
			break ;
		i++;
		n++;
	}
	i_ft_echo(cmd, i);
	if (n == 0)
		printf("\n");
	g_exit_status = 0;
	return (1);
}
