/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:21:57 by gekido            #+#    #+#             */
/*   Updated: 2025/05/22 01:37:33 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

char	*extract_var_name(char *str, int *i);
void	append_to_result(char **result, char c);
void	process_var_expansion(char *var_name, char **result, t_env *env);
void	handle_dollar_sign(char *str, int *i, char **result, t_env *env);
char	*expand_variables(char *str, t_env *env);
void	expand_token_variables(t_token *tokens, t_env *env);
char	*ft_strjoin_free(char *s1, char *s2);
char	*get_env_value(char *var, t_env *env);

#endif