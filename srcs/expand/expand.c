/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/14 14:12:05 by reeer-aa         ###   ########.fr       */
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

	str[0] = c;
	str[1] = '\0';
	temp = ft_strjoin(*result, str);
	if (temp)
	{
		free(*result);
		*result = temp;
	}
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

	(*i)++;
	if (str[*i] == '?' || ft_isdigit(str[*i]))
	{
		if (str[*i] == '?')
		{
			var_name = ft_itoa(g_signal_status);
			if (var_name)
				*result = ft_strjoin_free(*result, var_name);
			free(var_name);
		}
		(*i)++;
		return ;
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
	{
		append_to_result(result, '$');
		return ;
	}
	var_name = extract_var_name(str, i);
	if (var_name)
		process_var_expansion(var_name, result, env);
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
