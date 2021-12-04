/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:24:43 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/04 16:56:26 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *msh)
{
	size_t	i;

	i = -1;
	if (msh->cmd[0].args[1])
	{
		print_err_msg("env: ’",
			msh->cmd[0].args[1], "‘: No such file or directory\n");
		g_exit_status = 127;
		return (1);
	}
	while (msh->envp[++i])
	{
		if (ft_strchr(msh->envp[i], '='))
			printf("%s\n", msh->envp[i]);
	}
	g_exit_status = 0;
	return (1);
}
