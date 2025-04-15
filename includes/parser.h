/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:04:05 by gekido            #+#    #+#             */
/*   Updated: 2025/04/12 19:53:35 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_node_type
{
	NODE_COMMAND = 0,
	NODE_PIPE = 1,
	NODE_REDIR = 2
}	t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_redir				*redirects;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node		*parser(t_token *tokens);
t_ast_node		*parse_pipeline(t_token *token);
t_ast_node		*parse_command(t_token **token);

t_redir			*parse_redirections(t_token **token);
t_redir			*append_redirections(t_redir *list, t_redir *new);
int				is_redirection(t_token_type type);

t_ast_node		*create_command_node(char **args, t_redir *redirects);
t_ast_node		*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_redir			*create_redirection(t_token_type type, char *file);

int				count_word_tokens(t_token *token);
char			**extract_args(t_token **token, int count);
void			skip_to_next_token(t_token **token, int count);
int				is_pipe_token(t_token *token);

void			free_ast(t_ast_node *node);
void			free_redirections(t_redir *redirects);
void			free_args(char **args);

#endif