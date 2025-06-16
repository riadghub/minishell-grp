/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:25:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/16 11:24:10 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler_no_print(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal_status = 130;
}

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
	static pid_t	child_pid = 0;

	if (sig == SIGUSR1)
	{
		child_pid = 0;
		return ;
	}
	if (sig < 0)
	{
		child_pid = -sig;
		return ;
	}
	if (child_pid != 0)
	{
		kill(child_pid, SIGINT);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
