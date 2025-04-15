/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:11:15 by gekido            #+#    #+#             */
/*   Updated: 2025/01/31 10:11:16 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *string, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)string);
	while ((string[i] != '\0') && (needle[j] != '\0') && (i < len))
	{
		j = 0;
		if (string[i] == needle[0])
		{
			while (string[j + i] == needle[j] && ((i + j) < len))
			{
				if (needle[j + 1] == '\0')
					return ((char *)string + i);
				++j;
			}
		}
		i++;
	}
	return (NULL);
}
