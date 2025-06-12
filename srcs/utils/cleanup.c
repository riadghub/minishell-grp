/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:31 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/12 10:14:20 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_child_process(t_env *env)
{
	if (!env)
		return ;
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
}

void	cleanup_on_exit(t_env *env)
{
	if (!env)
		return ;
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
}
