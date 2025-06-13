/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:20:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/13 10:43:35 by reeer-aa         ###   ########.fr       */
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
	env->saved_stdin = -1;
	env->saved_stdout = -1;
	env->ast_cleanup = NULL;
	env->env_cleanup = NULL;
	env->vars[count] = NULL;
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
	close(env->saved_stdin);
	close(env->saved_stdout);
	free(env);
}
