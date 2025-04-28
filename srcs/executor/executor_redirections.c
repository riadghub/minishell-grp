/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:05:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/28 14:02:04 by reeer-aa         ###   ########.fr       */
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

void	handle_heredoc(t_redir *redir, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		sig;
	char	*line;

	if (pipe(fd) == -1)
		return ;
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
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	setup_signals();
	sig = status & 0x7f;
	if (sig == SIGINT)
	{
		env->exit_code = 130;
		close(fd[0]);
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	setup_redirections(t_redir *redirects, t_env *env)
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
			handle_heredoc(redirects, env);
		redirects = redirects->next;
	}
	return (result);
}
