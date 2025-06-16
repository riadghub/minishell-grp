/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/16 14:24:51 by reeer-aa         ###   ########.fr       */
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
	execute_ast_child(node->left, env);
	exit_code = g_signal_status;
	cleanup_child_process(env);
	exit(exit_code);
}

int	execute_pipe_parent(t_ast_node *node, t_env *env, int *pipefd, pid_t pid)
{
	int		status;
	pid_t	right_pid;
	int		right_status;

	close(pipefd[1]);
	right_pid = fork();
	if (right_pid == -1)
		return (close(pipefd[0]), waitpid(pid, &status, 0), 1);
	if (right_pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execute_ast_child(node->right, env);
		cleanup_child_process(env);
		exit(g_signal_status);
	}
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	waitpid(right_pid, &right_status, 0);
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	else
		return (1);
}
