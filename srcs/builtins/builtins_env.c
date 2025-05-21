/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:35:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/18 22:51:12 by gekido           ###   ########.fr       */
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

static char	**expand_env_tab(char **old, char *new_var, int size)
{
	char	**tab;
	int		j;

	tab = malloc(sizeof(char *) * (size + 2));
	if (!tab)
		return (NULL);
	j = 0;
	while (j < size)
	{
		tab[j] = old[j];
		j++;
	}
	tab[size] = new_var;
	tab[size + 1] = NULL;
	return (tab);
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
			if (ft_strncmp(env->vars[j], args[i], len) == 0)
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

static int	key_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	add_env_var(t_env *env, char *var)
{
	int		i;
	int		klen;
	char	*new;
	char	**tab;

	klen = key_len(var);
	new = ft_strdup(var);
	i = 0;
	while (env->vars[i])
	{
		if (ft_strncmp(env->vars[i], var, klen) == 0
			&& (env->vars[i][klen] == '\0' || env->vars[i][klen] == '='))
			return (free(env->vars[i]), env->vars[i] = new, (void)0);
		i++;
	}
	tab = expand_env_tab(env->vars, new, i);
	free(env->vars);
	env->vars = tab;
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
