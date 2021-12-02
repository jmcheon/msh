/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:24:43 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:24:44 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strchr_2(const char *s, int c)
{
    while (*s && *s != (char)c)
        s++;
    if (*s == (char)c)
        return (char*)s;
    return (NULL);
}

int    ft_env(t_minishell *msh)
{
    size_t    i;

    i = -1;
    while (msh->envp[++i])
    {
        if (ft_strchr(msh->envp[i], '='))
            printf("%s\n", msh->envp[i]);
    }
    msh->exit_status = 0;
    return (1);
}

int	ft_env_old(t_minishell *msh)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen_2dim((const char **)msh->envp))
		printf("%s\n", msh->envp[i]);
	msh->exit_status = 0;
	return (1);
}
