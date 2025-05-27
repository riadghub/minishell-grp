/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:21:57 by gekido            #+#    #+#             */
/*   Updated: 2025/05/27 14:20:14 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

typedef struct s_env	t_env;

char					*expand_variables(char *str, t_env *env);
char					*extract_var_name(char *str, int *i);
char					*get_env_value(char *key, t_env *env);
void					expand_token_variables(t_token *tokens, t_env *env);
char					*remove_quotes(char *str);
void					append_to_result(char **result, char c);
char					*ft_strjoin_free(char *s1, char *s2);
void					process_var_expansion(char *var_name, char **result,
							t_env *env);
void					handle_dollar_sign(char *str, int *i, char **result,
							t_env *env);

#endif