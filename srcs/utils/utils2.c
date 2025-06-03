/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:15:10 by gekido            #+#    #+#             */
/*   Updated: 2025/06/03 01:40:25 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_exit(void)
{
	if (g_signal_status >= 256)
		return (1);
	return (0);
}

int	get_exit_code(void)
{
	return (g_signal_status % 256);
}

int	process_input(char *input, t_env *env)
{
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	handle_command(input, env);
	free(input);
	if (g_signal_status >= 256)
		return (0);
	return (1);
}

void	close_fd(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

int	is_unknown_cmd(t_token *tokens, t_env *env)
{
	char	*path;
	char	*cmd;

	cmd = tokens->value;
	path = find_path(cmd, env->vars);
	if (!path)
	{
		// Check if it's a path (contains '/' or starts with './')
		if (ft_strchr(cmd, '/') || ft_strncmp(cmd, "./", 2) == 0)
		{
			// Check if file exists but is not executable
			if (access(cmd, F_OK) == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putendl_fd(": Permission denied", 2);
				g_signal_status = 126;
			}
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putendl_fd(": No such file or directory", 2);
				g_signal_status = 127;
			}
		}
		else
		{
			// Regular command not found in PATH
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd, 2);
			g_signal_status = 127;
		}
		return (1);
	}
	free(path);
	return (0);
}
