/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:36:14 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/16 14:43:39 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_count_parts(const char *str, const char *delim)
{
	int	count;
	int	delim_len;
	int	i;
	int	depth;

	count = 1;
	delim_len = ft_strlen(delim);
	depth = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			depth++;
		else if (str[i] == ')')
			depth--;
		else if (depth == 0 && ft_strncmp(str + i, delim, delim_len) == 0)
		{
			count++;
			i += delim_len - 1;
		}
		i++;
	}
	return (count);
}

static int	next_delim_level0(const char *str, const char *delim)
{
	int	i;
	int	depth;
	int	delim_len;

	i = 0;
	depth = 0;
	delim_len = ft_strlen(delim);
	while (str[i])
	{
		if (str[i] == '(')
			depth++;
		else if (str[i] == ')')
			depth--;
		else if (depth == 0 && ft_strncmp(str + i, delim, delim_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	init_variables(int *idx, int *p, int *start)
{
	*idx = 0;
	*p = 0;
	*start = 0;
}

char	**ft_split_array(const char *str, const char *delim)
{
	char	**res;
	int		start;
	int		idx;
	int		p;

	init_variables(&idx, &p, &start);
	res = malloc((ft_count_parts(str, delim) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (str[start])
	{
		idx = next_delim_level0(str + start, delim);
		if (idx == -1)
			idx = ft_strlen(str + start);
		res[p] = ft_strndup(str + start, idx);
		res[p] = ft_strtrim(res[p], "()");
		p++;
		start += idx;
		if (str[start])
			start += ft_strlen(delim);
		while (str[start] && str[start] == ' ')
			start++;
	}
	res[p] = NULL;
	return (res);
}
