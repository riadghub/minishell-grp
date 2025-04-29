/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:25:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/29 14:50:01 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_heredoc_pid = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_status = 130;
}

void	sig_handler(int sig)
{
	if (g_heredoc_pid != 0)
	{
		kill(g_heredoc_pid, sig);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
