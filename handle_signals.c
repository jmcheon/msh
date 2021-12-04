/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:07:17 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/03 16:07:18 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_signal(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	handle_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		g_exit_status = 130;
		close(STDIN_FILENO);
	}
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDIN_FILENO, "\n", 1);
		rl_redisplay();
		g_exit_status = 130;
		(void)signum;
	}
}
