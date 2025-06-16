/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:53:41 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/16 11:44:01 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	signal_hdl(int sig)
{
	(void)sig;
	printf("\r> ^C");
	close(STDIN_FILENO);
}

static int	heredoc_child_process(int *fd, t_redir *redir, t_env *env)
{
	char	*line;

	signal(SIGINT, signal_hdl);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	close(env->saved_stdin);
	close(env->saved_stdout);
	cleanup_child_process(env);
	_exit(0);
}

int	handle_heredoc(t_redir *redir, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (1);
	signal(SIGINT, sig_handler);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(fd, redir, env);
	sig_handler(-pid);
	close(fd[1]);
	waitpid(pid, &status, 0);
	sig_handler(SIGUSR1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}
