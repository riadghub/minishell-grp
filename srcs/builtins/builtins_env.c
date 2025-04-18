/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:35:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/18 13:28:06 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(t_env *env)
{
	int	i;

	i = 0;
	while (env->vars[i])
	{
		ft_putendl_fd(env->vars[i], 1);
		i++;
	}
	return (0);
}

void	print_export_entry(const char *entry)
{
	char		*eq;
	size_t		key_len;
	char		*key;
	const char	*value;

	eq = ft_strchr(entry, '=');
	if (!eq)
	{
		printf("export %s\n", entry);
		return ;
	}
	key_len = eq - entry;
	key = ft_substr(entry, 0, key_len);
	value = eq + 1;
	if (value[0] == '\0')
		printf("export %s=\"\"\n", key);
	else
		printf("export %s=\"%s\"\n", key, value);
	free(key);
}

int	export_builtin(char **args, t_env *env)
{
	int	i;

	if (!args[1])
	{
		i = 0;
		while (env->vars[i])
			print_export_entry(env->vars[i++]);
		return (0);
	}
	i = 1;
	while (args[i])
		add_env_var(env, args[i++]);
	return (0);
}

int	unset_builtin(char **args, t_env *env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (args[++i])
	{
		len = ft_strlen(args[i]);
		j = -1;
		while (env->vars[++j])
		{
			if (ft_strncmp(env->vars[j], args[i], len) == 0
				&& env->vars[j][len] == '=')
			{
				free(env->vars[j]);
				while (env->vars[j])
				{
					env->vars[j] = env->vars[j + 1];
					j++;
				}
				break ;
			}
		}
	}
	return (0);
}

void	add_env_var(t_env *env, char *var)
{
	int		i;
	int		len;
	char	*equal_sign;

	len = ft_strlen(var);
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		len = equal_sign - var;
	i = find_env_var_index(env->vars, var, len);
	if (i != -1)
	{
		free(env->vars[i]);
		env->vars[i] = ft_strdup(var);
		return ;
	}
	allocate_new_env(env, var);
}

void	update_env_var(t_env *env, char *key, char *value)
{
	char	*var;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	var = ft_strjoin(tmp, value);
	free(tmp);
	add_env_var(env, var);
	free(var);
}
