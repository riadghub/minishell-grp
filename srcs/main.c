/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:08:55 by gekido            #+#    #+#             */
/*   Updated: 2025/06/16 11:04:29 by reeer-aa         ###   ########.fr       */
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
	t_token		*first_non_empty;
	t_ast_node	*ast;

	add_history(input);
	tokens = lexer(input);
	if (!tokens)
		return ;
	expand_token_variables(tokens, env);
	first_non_empty = tokens;
	while (first_non_empty && first_non_empty->type == TOKEN_WORD
		&& (!first_non_empty->value || ft_strlen(first_non_empty->value) == 0))
		first_non_empty = first_non_empty->next;
	if (first_non_empty && first_non_empty->type == TOKEN_WORD
		&& !is_builtin(first_non_empty->value))
	{
		if (is_unknown_cmd(first_non_empty, env))
		{
			free_tokens(tokens);
			return ;
		}
	}
	ast = parser(tokens);
	free_tokens(tokens);
	if (ast)
		execute_ast(ast, env);
	free_ast(ast);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;
	int		exit_code;

	(void)argc;
	(void)argv;
	exit_code = 0;
	env = init_env(envp);
	if (!env)
		return (1);
	setup_signals();
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
	exit_code = get_exit_code();
	cleanup_on_exit(env);
	free_env(env);
	rl_clear_history();
	return (exit_code);
}
