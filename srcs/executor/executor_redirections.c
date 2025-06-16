/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:05:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/16 13:38:13 by reeer-aa         ###   ########.fr       */
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
			result = handle_heredoc(redirects, env);
		redirects = redirects->next;
	}
	return (result);
}
