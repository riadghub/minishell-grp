/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:39:15 by gekido            #+#    #+#             */
/*   Updated: 2025/05/23 14:54:33 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	append_to_result(char **result, char c)
{
	char	*tmp;
	char	str[2];

	if (!result || c == '\0')
		return ;
	str[0] = c;
	str[1] = '\0';
	if (*result)
		tmp = ft_strjoin(*result, str);
	else
		tmp = ft_strdup(str);
	if (!tmp)
		return ;
	free(*result);
	*result = tmp;
}

void	process_var_expansion(char *var_name, char **result, t_env *env)
{
	char	*var_value;

	var_value = get_env_value(var_name, env);
	if (var_value)
		*result = ft_strjoin_free(*result, var_value);
	free(var_name);
	free(var_value);
}

void	handle_dollar_sign(char *str, int *i, char **result, t_env *env)
{
	char	*var_name;
	char	*temp;

	(*i)++;
	if (str[*i] == '?')
	{
		temp = ft_itoa(env->exit_code);
		if (temp)
		{
			*result = ft_strjoin_free(*result, temp);
			free(temp);
		}
		(*i)++;
		return ;
	}
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return ;
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		append_to_result(result, '$');
	else
	{
		var_name = extract_var_name(str, i);
		if (var_name)
			process_var_expansion(var_name, result, env);
	}
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	char	quote;
	int		i;
	bool	in_single_quotes;

	result = ft_strdup("");
	quote = 0;
	if (!result)
		return (NULL);
	i = 0;
	in_single_quotes = false;
	while (str[i])
	{
		if (str[i] == '\'' && quote != '"')
			in_single_quotes = !in_single_quotes;
		if (str[i] == '$' && in_single_quotes)
			handle_dollar_sign(str, &i, &result, env);
		else
			append_to_result(&result, str[i++]);
	}
	return (result);
}
