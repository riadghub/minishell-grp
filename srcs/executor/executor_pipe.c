/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/03 11:31:31 by reeer-aa         ###   ########.fr       */
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
	int	exit_code;

	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
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
