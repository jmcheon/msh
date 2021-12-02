/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:24:32 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/11/30 17:24:33 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *str)
{
	int					sign;
	unsigned long long	res;
	long long			l;

	res = 0;
	sign = 1;
	l = 9223372036854775807;
	if (*str == '+' || *str == '-')
		sign -= 2 * (*str++ == '-');
	if (!*str)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if ((sign == 1 && res > .1 * (l - (*str - '0')))
			|| (sign == -1 && res > .1 * (l + 1 - (*str - '0'))))
			return (0);
		res = res * 10 + (*str++ - '0');
	}
	if (*str)
		return (0);
	return (1);
}

static long long	ft_atoi_exit(char *str)
{
	int					sign;
	unsigned long long	res;

	res = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
		sign -= 2 * (*str++ == '-');
	while (*str)
		res = res * 10 + (*str++ - '0');
	return ((long long)(sign * res));
}

int	ft_exit_pipe(t_minishell *msh, char **args)
{
	char			*temp;
	unsigned char	n;

	if (!args[1])
		return (0);
	if (!is_number(args[1]))
	{
		n = 2;
		print_err_msg("msh: exit: ", args[1], ": numeric argument required\n");
	}
	else if (args[2])
	{
		print_err_msg("msh: exit: ", NULL, "too many arguments\n");
		return (1);
	}
	else
		n = (unsigned char)ft_atoi_exit(args[1]);
	return (n);
}

int	ft_exit(t_minishell *msh, char **args)
{
	char			*temp;
	unsigned char	n;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
	{
		free_msh(msh, 0);
		exit(0);
	}
	if (!is_number(args[1]))
	{
		n = 2;
		print_err_msg("msh: exit: ", args[1], ": numeric argument required\n");
	}
	else if (args[2])
	{
		print_err_msg("msh: exit: ", NULL, "too many arguments\n");
		return (1);
	}
	else
		n = (unsigned char)ft_atoi_exit(args[1]);
	free_msh(msh, 0);
	exit(n);
}
