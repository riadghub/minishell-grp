/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/03 01:40:25 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(char **env)
{
	int		i;
	char	**paths;
	char	*path_var;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = env[i] + 5;
			paths = ft_split(path_var, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*try_path(char *cmd, char *dir)
{
	char	*tmp;
	char	*complete_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	complete_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!complete_path)
		return (NULL);
	if (access(complete_path, X_OK) == 0)
		return (complete_path);
	free(complete_path);
	return (NULL);
}

char	*search_in_paths(char *cmd, char **paths)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = try_path(cmd, paths[i]);
		if (path)
		{
			free_array(paths);
			return (path);
		}
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;

	if (ft_strchr(cmd, '/') || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	return (search_in_paths(cmd, paths));
}
