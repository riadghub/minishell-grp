/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:39:02 by gekido            #+#    #+#             */
/*   Updated: 2025/05/22 01:39:03 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

char	*get_env_value(char *var, t_env *env)
{
	int	i;
	int	len;

	/* on caste var pour ft_strcmp, qui prend char * */
	if (ft_strcmp((char *)var, "?") == 0)
		return (ft_itoa(env->exit_code));
	len = ft_strlen(var);
	i = 0;
	while (env->vars[i])
	{
		if (ft_strncmp(env->vars[i], var, len) == 0
			&& env->vars[i][len] == '=')
			return (ft_strdup(env->vars[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	expand_token_variables(t_token *tokens, t_env *env)
{
	t_token	*cur;
	char	*exp;

	cur = tokens;
	while (cur)
	{
		exp = expand_variables(cur->value, env);
		if (cur->type == TOKEN_WORD && exp)
		{
			free(cur->value);
			cur->value = exp;
		}
		else
			free(exp);
		cur = cur->next;
	}
}
