/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 01:32:51 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/04 15:54:28 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getvar(char *str)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = NULL;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (i <= 0)
		return (NULL);
	temp = ft_strdup_by_index(str, 0, i - 1);
	return (temp);
}

static int	ft_checkvar(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!str[0])
		return (0);
	if (str[0] && ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = -1;
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
	}
	return (1);
}

static int	ft_check_syntax(char *str)
{
	while (*str && *str != '+' && *str != '=')
		str++;
	if ((*str == '+' && *(str + 1) == '='))
		return (1);
	if (*str == '=')
		return (1);
	if (*str == '\0')
		return (1);
	return (0);
}

static	void	i_ft_export(t_minishell *msh, char **args)
{
	char	*var;
	int		len;
	int		mode;
	int		i;

	i = 0;
	var = NULL;
	while (args[++i])
	{
		var = ft_getvar(args[i]);
		if (ft_checkvar(var) == 0 || ft_check_syntax(args[i]) == 0)
		{
			print_err_msg("export: ", args[i], ": not a valid identifier\n");
			g_exit_status = 1;
		}
		else if (ft_strncmp(var, args[i], ft_strlen(args[i])))
		{
			len = ft_strlen(var);
			mode = (args[i][len] == '+' && args[i][len + 1] == '=');
			ft_setenv(msh, args[i], var, args[i] + len + 1 + mode);
		}
		else if (search_one_variable_path(msh, var) < 0)
			msh->envp = ft_strjoin_2dim_memdel(msh->envp, malloc_args(var));
		ft_memdel(&var);
	}
}

int	ft_export(t_minishell *msh, char **args)
{
	int		i;

	i = 0;
	if (!args[1])
	{
		while (msh->envp[i])
			printf("declare -x %s\n", msh->envp[i++]);
		return (1);
	}
	i_ft_export(msh, args);
	g_exit_status = 0;
	return (1);
}
