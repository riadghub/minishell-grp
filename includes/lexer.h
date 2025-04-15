/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:04:09 by gekido            #+#    #+#             */
/*   Updated: 2025/04/12 16:52:36 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);

t_token		*lexer(char *input);
int			is_special_char(char c);

void		handle_simple_operator(char *input, int *i, t_token **tokens);
void		handle_compound_operator(char *input, int *i, t_token **tokens);
void		handle_operator(char *input, int *i, t_token **tokens);

char		*get_word(char *input, int *i);
void		handle_normal_text(char *input, int *i, char **word);
void		extract_quoted_text(char *input, int *i, char **word, char quote);
void		handle_quotes(char *input, int *i, char **word);
int			should_stop_word(char *input, int i);

#endif