/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/17 21:58:05 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printbanner(void)
{
	ft_putendl_fd("\033[1;32m  __  __ _       _     _          _ _ ", 1);
	ft_putendl_fd(" |  \\/  (_)_ __ (_)___| |__   ___| | |", 1);
	ft_putendl_fd(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |", 1);
	ft_putendl_fd(" | |  | | | | | | \\__ \\ | | |  __/ | |", 1);
	ft_putendl_fd(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\033[0m", 1);
	ft_putendl_fd("", 1);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	is_valid_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	if (i > 1)
		return (1);
	return (0);
}
