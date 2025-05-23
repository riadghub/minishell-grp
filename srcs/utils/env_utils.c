/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:20:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/21 14:54:51 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->vars = malloc(sizeof(char *) * (count + 1));
	if (!env->vars)
		return (free(env), NULL);
	i = 0;
	while (i < count)
	{
		env->vars[i] = ft_strdup(envp[i]);
		i++;
	}
	env->vars[count] = NULL;
	env->exit_code = 0;
	return (env);
}

void	free_env(t_env *env)
{
	int	i;

	if (!env)
		return ;
	if (env->vars)
	{
		i = 0;
		while (env->vars[i])
			free(env->vars[i++]);
		free(env->vars);
	}
	free(env);
}
