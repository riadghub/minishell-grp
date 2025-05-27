/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:05:54 by gekido            #+#    #+#             */
/*   Updated: 2025/05/27 14:20:31 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_stop_word(char *input, int i)
{
	return (ft_is_space(input[i]) || input[i] == '|' || input[i] == '<'
		|| input[i] == '>' || input[i] == '\0');
}

void	handle_normal_text(char *input, int *i, char **word)
{
	char	*tmp;
	char	c[2];

	c[0] = input[*i];
	c[1] = '\0';
	tmp = ft_strjoin(*word, c);
	if (tmp)
	{
		free(*word);
		*word = tmp;
	}
	(*i)++;
}

void	extract_quoted_text(char *input, int *i, char **word, char quote)
{
	int		start;
	char	*substr;
	char	*tmp;
	char	quote_str[2];

	quote_str[0] = quote;
	quote_str[1] = '\0';
	tmp = ft_strjoin(*word, quote_str);
	if (tmp)
	{
		free(*word);
		*word = tmp;
	}
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (*i > start)
	{
		substr = ft_substr(input, start, *i - start);
		if (substr)
		{
			tmp = ft_strjoin(*word, substr);
			if (tmp)
			{
				free(*word);
				*word = tmp;
			}
			free(substr);
		}
	}
	if (input[*i] == quote)
	{
		tmp = ft_strjoin(*word, quote_str);
		if (tmp)
		{
			free(*word);
			*word = tmp;
		}
		(*i)++;
	}
}

void	handle_quotes(char *input, int *i, char **word)
{
	char	quote;

	quote = input[*i];
	extract_quoted_text(input, i, word, quote);
}

char	*get_word(char *input, int *i)
{
	char	*word;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*i] && !should_stop_word(input, *i))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quotes(input, i, &word);
		else
			handle_normal_text(input, i, &word);
		if (!word)
			return (NULL);
	}
	return (word);
}
