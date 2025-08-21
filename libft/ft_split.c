/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:54:49 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/21 11:49:22 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_parts(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != sep)
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*get_part(const char *str, char sep)
{
	char	*part;
	int		len;

	len = 0;
	while (str[len] && str[len] != sep)
		len++;
	part = (char *)malloc(sizeof(char) * (len + 1));
	if (!part)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != sep)
	{
		part[len] = str[len];
		len++;
	}
	part[len] = '\0';
	return (part);
}

char	**ft_free(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *str, char sep)
{
	int		i;
	int		k;
	char	**arr;

	i = 0;
	k = 0;
	arr = ft_calloc(sizeof(char *), (count_parts(str, sep) + 1));
	if (!arr || !str)
		return (ft_free(arr));
	while (str[i])
	{
		if (str[i] != sep)
		{
			arr[k] = get_part(&str[i], sep);
			if (!arr[k])
				return (ft_free(arr));
			while (str[i] && str[i] != sep)
				i++;
			k++;
		}
		else
			i++;
	}
	arr[k] = 0;
	return (arr);
}
