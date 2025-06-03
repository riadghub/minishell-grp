/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/23 14:41:08 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pipe(t_ast_node *node, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		execute_pipe_child(node, env, pipefd);
	g_signal_status = execute_pipe_parent(node, env, pipefd, pid);
	return (g_signal_status);
}

void	execute_pipe_child(t_ast_node *node, t_env *env, int *pipefd)
{
	int		exit_code;
	t_redir	*redir;
	int		has_output_redir;

	close(pipefd[0]);
	
	// Check if the left command has output redirections
	has_output_redir = 0;
	redir = node->left->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		{
			has_output_redir = 1;
			break;
		}
		redir = redir->next;
	}
	
	// If no output redirection, redirect to pipe
	if (!has_output_redir)
	{
		dup2(pipefd[1], STDOUT_FILENO);
	}
	close(pipefd[1]);
	
	execute_ast(node->left, env);
	free_ast(node);
	exit_code = g_signal_status;
	free_env(env);
	exit(exit_code);
}

int	execute_pipe_parent(t_ast_node *node, t_env *env, int *pipefd, pid_t pid)
{
	int	status;
	int	saved_stdin;
	int	right_exit_code;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (1);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	right_exit_code = execute_ast(node->right, env);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	waitpid(pid, &status, 0);
	return (right_exit_code);
}
