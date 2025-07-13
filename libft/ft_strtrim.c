/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:40:08 by lgertrud          #+#    #+#             */
/*   Updated: 2025/04/14 13:53:43 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(char ch, const char *set)
{
	while (*set)
	{
		if (ch == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;
	size_t	i;

	i = 0;
	start = 0;
	if (!s || !set)
		return (NULL);
	end = ft_strlen(s);
	while (s[start] && set_check(s[start], set))
		start++;
	while (end > start && set_check(s[end - 1], set))
		end--;
	res = (char *)malloc(end - start + 1);
	if (!res)
		return (NULL);
	while (start < end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
