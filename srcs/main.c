/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:08:55 by gekido            #+#    #+#             */
/*   Updated: 2025/05/02 10:53:10 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal_status = 0;

void	clean_all(t_env *env, t_token *tokens, t_ast_node *ast)
{
	if (ast)
		free_ast(ast);
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env(env);
	rl_clear_history();
}

void	handle_command(char *input, t_env *env)
{
	t_token		*tokens;
	t_ast_node	*ast;

	add_history(input);
	tokens = lexer(input);
	if (!tokens)
		return ;
	if (tokens->type == TOKEN_WORD && !is_builtin(tokens->value))
		if (is_unknown_cmd(tokens, env))
			return ;
	expand_token_variables(tokens, env);
	ast = parser(tokens);
	if (ast)
	{
		execute_ast(ast, env);
		free_ast(ast);
	}
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;
	int		exit_code;

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
		if (!process_input(input, env))
			break ;
	}
	exit_code = env->exit_code;
	return (clean_all(env, NULL, NULL), exit_code);
}
