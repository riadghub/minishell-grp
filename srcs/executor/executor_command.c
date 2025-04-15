/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:40:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/14 13:24:08 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_ast(t_ast_node *node, t_env *env)
{
	int	exit_status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		exit_status = execute_command(node, env);
	else if (node->type == NODE_PIPE)
		exit_status = execute_pipe(node, env);
	else
		exit_status = 1;
	return (exit_status);
}

int	execute_builtin(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		echo_builtin(args, env);
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
		return (exit_builtin(args));
	return (1);
}

int	execute_command_node(t_ast_node *node, t_env *env)
{
	char	**args;
	int		exit_status;

	args = node->args;
	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		exit_status = execute_builtin(args, env);
	else
	{
		execute_external(node, env);
		exit_status = env->exit_code;
	}
	return (exit_status);
}

int	execute_command(t_ast_node *node, t_env *env)
{
	int		saved_stdin;
	int		saved_stdout;
	int		exit_status;
	t_redir	*redirections;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redirections = node->redirects;
	if (setup_redirections(redirections) != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	exit_status = execute_command_node(node, env);
	restore_std_fds(saved_stdin, saved_stdout);
	return (exit_status);
}
