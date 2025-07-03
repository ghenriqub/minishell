/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:15:44 by lgertrud          #+#    #+#             */
/*   Updated: 2025/04/14 14:04:02 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	space;
	size_t	x;

	dest_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (size <= dest_size)
	{
		return (size + src_size);
	}
	space = size - dest_size - 1;
	x = 0;
	while (x < space && src[x])
	{
		dst[dest_size + x] = src[x];
		x++;
	}
	dst[dest_size + x] = '\0';
	return (dest_size + src_size);
}
