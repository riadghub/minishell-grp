/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:08:55 by gekido            #+#    #+#             */
/*   Updated: 2025/04/11 18:24:12 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_status = 0;

void	handle_command(char *input, t_env *env)
{
	t_token		*tokens;
	t_ast_node	*ast_root;

	add_history(input);
	tokens = lexer(input);
	if (tokens)
	{
		expand_token_variables(tokens, env);
		ast_root = parser(tokens);
		if (ast_root)
		{
			execute_ast(ast_root, env);
			free_ast(ast_root);
		}
		free_tokens(tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	setup_signals();
	printbanner();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		handle_command(input, env);
		free(input);
	}
	return (free_env(env), rl_clear_history(), 0);
}
