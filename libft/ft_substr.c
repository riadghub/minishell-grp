/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:11:25 by gekido            #+#    #+#             */
/*   Updated: 2025/01/31 10:11:26 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = (size_t)start;
	j = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char const) * (len + 1));
	if ((size_t)start >= ft_strlen((char *)s))
		return (str);
	if (!str)
		return (NULL);
	while (s[i] && (j < len))
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
