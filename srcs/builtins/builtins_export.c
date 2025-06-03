/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:41:22 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/03 01:40:25 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	sort_strings(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export(const char *s)
{
	const char	*eq = s;
	int			len;

	while (*eq && *eq != '=')
		eq++;
	write(1, "export ", 7);
	write(1, s, eq - s);
	write(1, "=\"", 2);
	if (*eq == '=')
	{
		eq++;
		len = 0;
		while (eq[len])
			len++;
		write(1, eq, len);
	}
	write(1, "\"\n", 2);
}

static int	print_sorted_env(t_env *env)
{
	int		n;
	char	**sorted;
	int		i;

	n = ft_tablen(env->vars);
	sorted = malloc(sizeof(char *) * (n + 1));
	if (!sorted)
		return (1);
	i = 0;
	while (i < n)
	{
		sorted[i] = env->vars[i];
		i++;
	}
	sorted[n] = NULL;
	sort_strings(sorted, n);
	i = 0;
	while (i < n)
	{
		print_export(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

int	export_builtin(char **args, t_env *env)
{
	int	i;

	if (!args[1])
		return (print_sorted_env(env));
	i = 1;
	while (args[i])
	{
		add_env_var(env, args[i]);
		i++;
	}
	return (g_signal_status % 256);
}
