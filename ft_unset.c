/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:12:18 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:12:24 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var(char *str)
{
	if ((*str >= '0' && *str <= '9'))
		return (0);
	if (*str == '$')
		str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	i_ft_unset(t_minishell *msh, char **args, size_t i)
{
	char	**tmp_args;
	int		n;

	tmp_args = NULL;
	n = search_one_variable_path(msh, (args)[i]);
	if (n >= 0)
	{
		tmp_args = msh->envp;
		msh->envp = ft_strtrim_2dim_by_index(
				(const char **)msh->envp, n, n);
		ft_memdel_2dim(&tmp_args);
	}
}

int	ft_unset(t_minishell *msh, char **args)
{
	size_t	i;
	int		err;

	i = 0;
	err = 0;
	while (i < ft_strlen_2dim((const char **)args))
	{
		if (!is_valid_var((args)[i]))
		{
			print_err_msg("unset: ", args[i++], ": not a valid identifier\n");
			err = 1;
			continue ;
		}
		i_ft_unset(msh, args, i++);
	}
	if (err == 1)
		g_exit_status = 1;
	else
		g_exit_status = 0;
	return (1);
}
