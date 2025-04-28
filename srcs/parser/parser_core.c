/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:10:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/21 23:45:37 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe_token(t_token *token)
{
	return (token && token->type == TOKEN_PIPE);
}

void	skip_to_next_token(t_token **token, int count)
{
	int	i;

	i = 0;
	while (i < count && *token)
	{
		*token = (*token)->next;
		i++;
	}
}

t_ast_node	*parser(t_token *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*current;
	t_ast_node	*pipe_node;

	if (!tokens)
		return (NULL);
	current = tokens;
	left = parse_command(&current);
	if (!left)
		return (NULL);
	if (is_pipe_token(current))
	{
		skip_to_next_token(&current, 1);
		right = parser(current);
		if (!right)
			return (free_ast(left), NULL);
		pipe_node = create_pipe_node(left, right);
		if (!pipe_node)
			return (free_ast(left), free_ast(right), NULL);
		return (pipe_node);
	}
	return (left);
}

t_ast_node	*parse_command(t_token **token)
{
	int		word_count;
	char	**args;
	t_redir	*redirects;

	word_count = count_word_tokens(*token);
	if (word_count == 0 && !is_redirection((*token)->type))
		return (NULL);
	args = extract_args(token, word_count);
	if (!args && word_count > 0)
		return (NULL);
	redirects = parse_redirections(token);
	return (create_command_node(args, redirects));
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free_args(node->args);
	free_redirections(node->redirects);
	free(node);
}
