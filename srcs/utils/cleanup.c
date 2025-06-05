/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:31 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/05 10:04:08 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_child_process(void)
{
	if (g_ast_cleanup)
	{
		free_ast(g_ast_cleanup);
		g_ast_cleanup = NULL;
	}
	if (g_env_cleanup)
	{
		free_env(g_env_cleanup);
		g_env_cleanup = NULL;
	}
	rl_clear_history();
}

void	cleanup_on_exit(void)
{
	cleanup_child_process();
}
