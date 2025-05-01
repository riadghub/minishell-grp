/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:05:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/01 12:42:11 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_redirection_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	setup_redirection_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putendl_fd(": Cannot open file", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	setup_redirection_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putendl_fd(": Cannot open file", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	handle_heredoc(t_redir *redir)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		return ;
	signal(SIGINT, sig_handler);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, redir->file) == 0)
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	sig_handler(-pid);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	sig_handler(SIGUSR1);
	setup_signals();
}

int	setup_redirections(t_redir *redirects)
{
	int	result;

	result = 0;
	while (redirects && result == 0)
	{
		if (redirects->type == TOKEN_REDIR_IN)
			result = setup_redirection_in(redirects);
		else if (redirects->type == TOKEN_REDIR_OUT)
			result = setup_redirection_out(redirects);
		else if (redirects->type == TOKEN_APPEND)
			result = setup_redirection_append(redirects);
		else if (redirects->type == TOKEN_HEREDOC)
			handle_heredoc(redirects);
		redirects = redirects->next;
	}
	return (result);
}
