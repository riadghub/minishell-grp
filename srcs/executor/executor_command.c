/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:40:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/03 01:40:25 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		g_signal_status = execute_command(node, env);
	else if (node->type == NODE_PIPE)
		g_signal_status = execute_pipe(node, env);
	else
		g_signal_status = 1;
	return (g_signal_status % 256);
}

int	execute_builtin(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo_builtin(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd_builtin(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd_builtin());
	else if (ft_strcmp(args[0], "export") == 0)
		return (export_builtin(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset_builtin(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env_builtin(env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (exit_builtin(args, env));
	return (1);
}

int	execute_command_node(t_ast_node *node, t_env *env)
{
	char	**args;

	args = node->args;
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], ".") == 0)
	{
		ft_putendl_fd(".: filename argument required", 2);
		return (ft_putendl_fd(".: usage: . filename [arguments]", 2), 2);
	}
	if (args[0][0] == '.' && args[0][1] == '.')
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		return (ft_putendl_fd(args[0], 2), 127);
	}
	if (is_builtin(args[0]))
		g_signal_status = execute_builtin(args, env);
	else
		execute_external(node, env);
	return (g_signal_status % 256);
}

int	execute_command(t_ast_node *node, t_env *env)
{
	int		saved_stdin;
	int		saved_stdout;
	t_redir	*redirections;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (close_fd(saved_stdin, saved_stdout), 1);
	redirections = node->redirects;
	if (setup_redirections(redirections) != 0)
		return (restore_std_fds(saved_stdin, saved_stdout), 1);
	g_signal_status = execute_command_node(node, env);
	return (restore_std_fds(saved_stdin, saved_stdout), g_signal_status % 256);
}
