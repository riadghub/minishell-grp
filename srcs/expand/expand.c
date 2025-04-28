/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/22 01:18:02 by gekido           ###   ########.fr       */
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
	char	*temp;
	char	str[2];

	if (!result || c == '\0')
		return ;
	str[0] = c;
	str[1] = '\0';
	if (*result)
		temp = ft_strjoin(*result, str);
	else
		temp = ft_strdup(str);
	if (!temp)
		return ;
	free(*result);
	*result = temp;
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
		return ((*i)++, (void)0);
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
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			handle_dollar_sign(str, &i, &result, env);
		else
			append_to_result(&result, str[i++]);
	}
	return (result);
}
