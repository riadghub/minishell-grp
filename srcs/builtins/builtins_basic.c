/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/23 14:32:14 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_builtin(char **args, t_env *env)
{
	char	cwd[1024];
	char	*path;

	if (ft_tablen(args) > 2)
		return (ft_putendl_fd("minishell: too many arguments", 2), 1);
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_env_value("HOME", env);
		if (!path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	}
	else
		path = ft_strdup(args[1]);
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free(path);
		return (1);
	}
	if (getcwd(cwd, 1024))
		update_env_var(env, "PWD", cwd);
	free(path);
	return (0);
}

int	echo_builtin(char **args)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (0);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args, t_env *env)
{
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		g_signal_status = 256;
		return (0);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_signal_status = 256 + 2;
		env->exit_code = g_signal_status;
		return (env->exit_code);
	}
	if (args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	env->exit_code = ft_atoi(args[1]);
	if (env->exit_code < 0)
		env->exit_code = 256 + (env->exit_code % 256);
	else
		env->exit_code = env->exit_code % 256;
	g_signal_status = 256 + env->exit_code;
	return (env->exit_code);
}

int	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
}
