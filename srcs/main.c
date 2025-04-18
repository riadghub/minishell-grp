/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:08:55 by gekido            #+#    #+#             */
/*   Updated: 2025/04/18 13:53:30 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal_status = 0;

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

int	is_posix_mode(int argc, char **argv)
{
	int	posix;
	int	i;

	posix = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--posix") == 0)
			posix = 1;
		i++;
	}
	return (posix);
}

void	print_banner_if_needed(int posix)
{
	if (!posix)
		printbanner();
}

char	*get_prompt_for(int posix)
{
	char	*prompt;

	if (posix)
		prompt = ft_strdup("> ");
	else
		prompt = ft_strdup("minishell$ ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;
	int		cont;
	int		exit_code;
	char	*prompt;

	env = init_env(envp);
	setup_signals();
	print_banner_if_needed(is_posix_mode(argc, argv));
	cont = 1;
	while (cont)
	{
		prompt = get_prompt_for(is_posix_mode(argc, argv));
		input = readline(prompt);
		free(prompt);
		cont = process_input(input, env);
	}
	exit_code = env->exit_code;
	free_env(env);
	rl_clear_history();
	if (g_signal_status < 256)
		close_fd(STDIN_FILENO, STDOUT_FILENO);
	return (exit_code);
}
