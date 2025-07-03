/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:27:43 by lgertrud          #+#    #+#             */
/*   Updated: 2025/04/14 14:00:04 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	num;
	void	*p;

	num = nmemb * size;
	p = malloc(num);
	if (!p)
		return (NULL);
	ft_memset(p, 0, num);
	return (p);
}
