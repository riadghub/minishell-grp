/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 02:50:34 by gekido            #+#    #+#             */
/*   Updated: 2025/04/12 14:55:13 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_new_env(t_env *env, char *var)
{
	int		i;
	char	**new_vars;

	i = 0;
	while (env->vars[i])
		i++;
	new_vars = malloc(sizeof(char *) * (i + 2));
	if (!new_vars)
		return ;
	i = -1;
	while (env->vars[++i])
		new_vars[i] = env->vars[i];
	new_vars[i] = ft_strdup(var);
	new_vars[i + 1] = NULL;
	free(env->vars);
	env->vars = new_vars;
}

int	find_env_var_index(char **vars, char *var, int len)
{
	int	i;

	i = 0;
	while (vars[i])
	{
		if (ft_strncmp(vars[i], var, len) == 0 && vars[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
