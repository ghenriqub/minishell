/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:50:55 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/23 14:59:38 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_join_free(char *s1, const char *s2)
{
	char	*new;
	int		len1;
	int		len2;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	if (s1)
	{
		ft_memcpy_gnl(new, s1, len1);
		free(s1);
	}
	ft_memcpy_gnl(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	return (new);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	dest = (char *)malloc((n + 1) * sizeof(char));
	if (!dest)
	{
		return (NULL);
	}
	i = 0;
	while (i < n && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
