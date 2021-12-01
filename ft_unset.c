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

int	search_one_variable_path(t_minishell *msh, char *variable)
{
	char	**args;
	size_t	i;

	i = 0;
	args = NULL;
	while (msh->envp[i] != NULL
		&& ft_strncmp(msh->envp[i], variable, ft_strlen(variable)) != 0)
		i++;
	if (msh->envp[i] == NULL)
		return (-1);
	if (!ft_strncmp(msh->envp[i], variable, ft_strlen(variable)))
	{
		if (msh->envp[i][ft_strlen(variable) + 1] == '=')
		{
			args = ft_split(msh->envp[i], '=');
			if (ft_strcmp(args[0], variable) != 0)
			{
				ft_memdel_2dim(&args);
				return (-1);
			}
		}
	}
	ft_memdel_2dim(&args);
	return (i);
}

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

void	ft_unset(t_minishell *msh, char **args)
{
	char	**tmp_args;
	int		i;
	int		n;

	tmp_args = NULL;
	i = -1;
	n = -1;
	while (++i < ft_strlen_2dim((const char **)args))
	{
		if (!is_valid_var((args)[i]))
		{
			print_err_msg("unset: ", args[i++], ": not a valid identifier\n");
			msh->exit_status = 1;
			continue ;
		}
		n = search_one_variable_path(msh, (args)[i]);
		if (n >= 0)
		{
			tmp_args = msh->envp;
			msh->envp = ft_strtrim_2dim_by_index(
					(const char **)msh->envp, n, n);
			ft_memdel_2dim(&tmp_args);
		}
		msh->exit_status = 0;
	}
}
