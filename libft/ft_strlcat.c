/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:10:57 by gekido            #+#    #+#             */
/*   Updated: 2025/01/31 10:10:58 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lenstr;
	size_t	i;

	lendst = 0;
	lenstr = 0;
	i = 0;
	while (dst[lendst] && lendst < size)
		lendst++;
	while (src[lenstr])
		lenstr++;
	if (size == 0)
		return (lenstr);
	while (src[i] && (lendst + i + 1) < size)
	{
		dst[lendst + i] = src[i];
		i++;
	}
	if (lendst != size)
		dst[lendst + i] = '\0';
	if (lendst >= size)
		return (lenstr + size);
	return (lendst + lenstr);
}
