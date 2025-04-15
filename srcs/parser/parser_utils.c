/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:13:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/12 16:29:29 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == TOKEN_WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**extract_args(t_token **token, int count)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		args[i] = ft_strdup((*token)->value);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		*token = (*token)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_redir	*append_redirections(t_redir *list, t_redir *new)
{
	t_redir	*current;

	if (!list)
		return (new);
	if (!new)
		return (list);
	current = list;
	while (current->next)
		current = current->next;
	current->next = new;
	return (list);
}

t_redir	*parse_redirections(t_token **token)
{
	t_redir	*redirects;
	t_redir	*new_redir;

	redirects = NULL;
	while (*token && is_redirection((*token)->type))
	{
		if (!(*token)->next || (*token)->next->type != TOKEN_WORD)
			return (free_redirections(redirects), NULL);
		new_redir = create_redirection((*token)->type, (*token)->next->value);
		if (!new_redir)
			return (free_redirections(redirects), NULL);
		redirects = append_redirections(redirects, new_redir);
		*token = (*token)->next->next;
	}
	return (redirects);
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}
