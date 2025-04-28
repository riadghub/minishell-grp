/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/22 00:55:54 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	handle_simple_operator(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		add_token(tokens, create_token(TOKEN_PIPE, "|"));
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		add_token(tokens, create_token(TOKEN_REDIR_IN, "<"));
		(*i)++;
	}
}

void	handle_compound_operator(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, create_token(TOKEN_HEREDOC, "<<"));
		(*i) += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, create_token(TOKEN_APPEND, ">>"));
		(*i) += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(tokens, create_token(TOKEN_REDIR_OUT, ">"));
		(*i)++;
	}
}

void	handle_operator(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, create_token(TOKEN_HEREDOC, "<<"));
		(*i) += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, create_token(TOKEN_APPEND, ">>"));
		(*i) += 2;
	}
	else if (input[*i] == '|')
	{
		add_token(tokens, create_token(TOKEN_PIPE, "|"));
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		add_token(tokens, create_token(TOKEN_REDIR_IN, "<"));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		add_token(tokens, create_token(TOKEN_REDIR_OUT, ">"));
		(*i)++;
	}
}
