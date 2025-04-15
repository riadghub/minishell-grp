/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:53:46 by rbourkai          #+#    #+#             */
/*   Updated: 2025/04/08 21:07:24 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc_stash(char *stash, char *buffer)
{
	char	*new_stash;

	if (!buffer)
		return (NULL);
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	new_stash = ft_strjoin(stash, buffer);
	free(stash);
	return (new_stash);
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*temp;
	char	*newline_pos;
	size_t	line_len;

	if (!*stash || !**stash)
		return (free(*stash), *stash = NULL, NULL);
	newline_pos = ft_strchr(*stash, '\n');
	if (!newline_pos)
		return (line = ft_strdup(*stash), free(*stash), *stash = NULL, line);
	line_len = newline_pos - *stash + 1;
	line = malloc(line_len + 1);
	if (!line)
		return (free(*stash), *stash = NULL, NULL);
	ft_memmove(line, *stash, line_len);
	line[line_len] = '\0';
	temp = ft_strdup(newline_pos + 1);
	free(*stash);
	*stash = temp;
	if (!temp && line)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), stash = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stash), stash = NULL, NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0 && (!stash || *stash == '\0'))
			return (free(buffer), free(stash), stash = NULL, NULL);
		stash = alloc_stash(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (free(buffer), extract_line(&stash));
}
