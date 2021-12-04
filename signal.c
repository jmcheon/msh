/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:07:04 by cjung-mo          #+#    #+#             */
/*   Updated: 2021/12/03 16:07:05 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	listen_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	listen_signals_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	listen_signals_child(void)
{
	signal(SIGINT, handle_child_signal);
	signal(SIGQUIT, handle_child_signal);
}
