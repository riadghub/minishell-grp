/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:56:19 by gekido            #+#    #+#             */
/*   Updated: 2025/05/21 16:25:08 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;
	t_token	*new_token;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]))
			i++;
		else if (is_special_char(input[i]))
			handle_operator(input, &i, &tokens);
		else
		{
			word = get_word(input, &i);
			if (!word)
				return (free_tokens(tokens), NULL);
			if (word[0] != '\0')
			{
				new_token = create_token(TOKEN_WORD, word);
				if (!new_token)
					return (free(word), free_tokens(tokens), NULL);
				add_token(&tokens, new_token);
			}
			free(word);
		}
	}
	return (tokens);
}
