/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:55:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/16 14:24:46 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**convert_env_to_array(t_env *env)
{
	return (env->vars);
}

char	**duplicate_env_vars(char **env_vars)
{
	char	**dup_env;
	int		count;
	int		i;

	if (!env_vars)
		return (NULL);
	count = 0;
	while (env_vars[count])
		count++;
	dup_env = malloc(sizeof(char *) * (count + 1));
	if (!dup_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup_env[i] = ft_strdup(env_vars[i]);
		if (!dup_env[i])
		{
			while (i > 0)
				free(dup_env[--i]);
			free(dup_env);
			return (NULL);
		}
		i++;
	}
	dup_env[count] = NULL;
	return (dup_env);
}

void	parent_process(pid_t pid, t_env *env)
{
	int	status;

	(void)env;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_signal_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal_status = 128 + WTERMSIG(status);
}

typedef struct s_child_data
{
	char		*path;
	char		**args;
	char		**env_vars;
}				t_child_data;

t_child_data	*prepare_child_data(t_ast_node *node, t_env *env)
{
	t_child_data	*data;
	int				i;

	data = malloc(sizeof(t_child_data));
	if (!data)
		return (NULL);
	data->path = find_path(node->args[0], env->vars);
	if (!data->path)
	{
		free(data);
		return (NULL);
	}
	i = 0;
	while (node->args[i])
		i++;
	data->args = malloc(sizeof(char *) * (i + 1));
	if (!data->args)
	{
		free(data->path);
		free(data);
		return (NULL);
	}
	i = 0;
	while (node->args[i])
	{
		data->args[i] = ft_strdup(node->args[i]);
		if (!data->args[i])
		{
			while (i > 0)
				free(data->args[--i]);
			free(data->args);
			free(data->path);
			free(data);
			return (NULL);
		}
		i++;
	}
	data->args[i] = NULL;
	data->env_vars = duplicate_env_vars(env->vars);
	if (!data->env_vars)
	{
		free_array(data->args);
		free(data->path);
		free(data);
		return (NULL);
	}
	return (data);
}

void	free_child_data(t_child_data *data)
{
	if (!data)
		return ;
	if (data->path)
		free(data->path);
	if (data->args)
		free_array(data->args);
	if (data->env_vars)
		free_array(data->env_vars);
	free(data);
}

void	minimal_child_process(t_child_data *data, t_env *env)
{
	if (env->ast_cleanup)
	{
		free_ast(env->ast_cleanup);
		env->ast_cleanup = NULL;
	}
	if (env->env_cleanup)
	{
		free_env(env->env_cleanup);
		env->env_cleanup = NULL;
	}
	free_env(env);
	rl_clear_history();
	if (execve(data->path, data->args, data->env_vars) == -1)
	{
		ft_putstr_fd("minishell: error executing: ", 2);
		ft_putendl_fd(data->args[0], 2);
		exit(126);
	}
}

void	execute_external(t_ast_node *node, t_env *env)
{
	pid_t			pid;
	t_child_data	*child_data;

	signal(SIGINT, sigint_handler_no_print);
	child_data = prepare_child_data(node, env);
	if (!child_data)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		g_signal_status = 127;
		setup_signals();
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_child_data(child_data);
		return ;
	}
	if (pid == 0)
		minimal_child_process(child_data, env);
	else
	{
		free_child_data(child_data);
		parent_process(pid, env);
	}
	setup_signals();
}
